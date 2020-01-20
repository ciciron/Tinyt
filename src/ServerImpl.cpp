#include <algorithm>
#include <iostream>
#include <sstream>
#include <sys/time.h>

#include "tsapi.h"
#include "server.h"
#include "command.h"

extern int verbose_flag;

//Static & API
IServer *EntryPoint()
{
    return Service::EntryPoint();
}

Service *Service::EntryPoint()
{
    return instance.get(); 
}

//Constructors
Service::Service()
{
    client = nullptr;
    objEnumerator = 0;
    comEnumerator = 0;
    realm = std::make_unique<Realm>();
    term = promTerm.get_future();
    for (unsigned int thrNo = 0; thrNo < std::thread::hardware_concurrency() ; thrNo++)
    {
        std::thread thr ([](Service* ctx)
        {
            while(1)
            {
                int rdyComms = ctx->Worker();
                ctx->NotifyClient(rdyComms);
                if (ctx->term.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
                    break;
            }
        }, this);
        thrds.push_back(std::move(thr));
    }
};

Service::~Service()
{
    if (verbose_flag)
    {
        std::stringstream ssInfo;
        ssInfo << "Tinyt: Destruction. Inque " << comQue.size() << " pcs." << std::endl;
        std::cout << ssInfo.str();
    }
        
    promTerm.set_value();
    while(!thrds.empty())
    {
        std::thread thr = std::move(thrds.front());
        thrds.pop_front();
        thr.join();
    }
    comStore.clear();
    comInproc.clear();
    comRdy.clear();
    comQue.clear();
};

int Service::GenCommandId()
{
    return ++comEnumerator;
}

MoveableObject *Service::Mo(int number)
{
    auto query = objects.find(number);
    if (query != objects.end())
        return query->second.get();
    return nullptr;
}

//API
RStatus Service::CreateCommand(Action action, int executorId, int toutSec, ICommand **coRef) 
{ 
    std::shared_ptr<CommandBase> comm;
    ICommand *ic;
    RStatus rv = RStatus::Error;
    try
    {
        switch (action)
        {
            case Action::Move:
                comm = std::make_shared<CommandMove>(this, toutSec);
                rv = RStatus::Success;
                break;
            case Action::Test:
                comm = std::make_shared<CommandTest>(this, toutSec);
                rv = RStatus::Success;
                break;
        }
        if (rv != RStatus::Success)
            return rv;
        comm->SetExecutor(executorId);
        if (!coRef)
            return RStatus::Error;
        comm->CltSideUp();
        ic = static_cast<ICommand*>(comm.get());
        coRef[0] = ic;
        std::lock_guard<std::mutex> csLock(mutcstore);
        comStore.insert(std::make_pair(ic->Id(), std::move(comm)));
        if (verbose_flag)
            printf("Create command #%d, Ex:%d\n",ic->Id(), executorId);
    } catch(...)
    {
        rv = RStatus::Error;
        puts("Tinyt: Create command with error(except).");
    }
    return rv;
}

RStatus Service::ExecuteCommand(int commId)
{
    std::lock_guard<std::mutex> csLock(mutcstore);
    RStatus rv = RStatus::Refuse;
    //Check execute twice
    if (comInproc.count(commId) > 0)
    {
        if (verbose_flag)
            printf("Tinyt: Warn. Command %d executing now.", commId);
        return rv;
        
    }
    //Check execute completed command
    if (comRdy.count(commId) > 0)
    {
        if (verbose_flag)
            printf("Tinyt: Warn. Command %d has been executed.", commId);
        return rv;
    }
    auto next = comStore.find(commId);
    if (next != comStore.end())
    {
        std::shared_ptr<CommandBase> command;
        ExecutionEnum exType;
        command = std::move(next->second);
        comStore.erase(next);
        exType = command->ExecutionType();
        if (exType == ExecutionEnum::Async)
        {
            comInproc.insert(std::make_pair(command->Id(), command));
            command->Launch(time(NULL));
            rv = Launch(command.get());
        } else
            rv = Exec(command.get());
    }
    return rv;
}

RStatus Service::CreateMoveable(int desireX, int desireY, int &moId)
{
    RStatus rv = RStatus::Refuse;
    try 
    {
        std::unique_ptr<MoveableObject> mo = std::make_unique<MoveableObject>();
        if (realm->BestPlacement(mo.get(), desireX, desireY))
        {
            std::lock_guard<std::mutex> lock(mutObjects);
            moId = ++objEnumerator;
            mo->Id = moId;
            objects.insert(std::make_pair(moId, std::move(mo)));
            rv = RStatus::Success;
            if (verbose_flag)
            {
                printf("Create object #%d at (%d, %d)\n", moId, desireX, desireY);
            }
        } else
            if (verbose_flag)
                printf("Placement to (%d, %d) failed.\n", desireX, desireY);
                
    } catch (...)
    {
        puts("Tinyt: Create MO failed(except).");
    }
    return rv;
}

RStatus Service::GetDimSize(int &capX, int &capY)
{
    capX = realm->AreaX;
    capY = realm->AreaY;
    return RStatus::Success;
}

void Service::CallbackSet(ICallback *intrfc)
{
    std::lock_guard<std::mutex> csLock(mutCallback);
    client = intrfc;
}
void Service::CallbackClear()
{
    std::lock_guard<std::mutex> csLock(mutCallback);
    client = nullptr;
}


//Realm test routine
RStatus Service::Test()
{
    bool srvcPassed = realm->Test();
    
    return srvcPassed ? RStatus::Success : RStatus::Refuse;
}


//-=P.R.I.V.A.T.E.=-
RStatus Service::Exec(CommandBase *comBase)
{
    return comBase->Invoke();
}

RStatus Service::Launch(CommandBase *comBase)
{
    comQue.push_back(comBase);
    queNotify.notify_one();
    return RStatus::Async;
}

size_t Service::Worker()
{
    std::unique_lock<std::mutex> unimutCapture(mutcstore);
    RStatus invokeStatus;
    CommandBase* basic = nullptr;
    size_t rv = 0;
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (queNotify.wait_for(unimutCapture, std::chrono::milliseconds(50), [this] {return !this->comQue.empty();}))
    {
        if (!comQue.empty())
        {
            basic = this->comQue.front();
            comQue.pop_front();
        }
    } else
        return 0;
    unimutCapture.unlock();
    invokeStatus = basic->Invoke();
    unimutCapture.lock();
    switch(invokeStatus)
    {
        case RStatus::Async:
            comQue.push_back(basic);
            queNotify.notify_one();
            break;
        case RStatus::Refuse:
            if (verbose_flag)
                printf("Tinyt: Command #%d refuse.\n", basic->Id());
        case RStatus::Success:
            if (comInproc.count(basic->Id()) > 0)
            {
                std::shared_ptr<CommandBase> basicShar;
                basicShar = std::move(comInproc[basic->Id()]);
                comInproc.erase(basic->Id());
                comRdy.insert(std::make_pair(basic->Id(), std::move(basicShar)));
                if (verbose_flag)
                    printf("Tinyt: Complete #%d.\n", basic->Id());
                rv = comRdy.size();
            } else
                printf("Tinyt: Warn. Command #%d not present in Inproc.\n", basic->Id());
            break;
        default:
            if (verbose_flag)
                printf("Tinyt: Command #%d return bad status.\n", basic->Id());
            break;
    }
    return rv;
}

void Service::NotifyClient(int nums)
{
    std::list <std::shared_ptr<CommandBase>> comsOut;
    if (nums > 0)
    {
        std::lock_guard<std::mutex> guard(mutcstore);
        while (!comRdy.empty())
        {
            std::shared_ptr<CommandBase> completed = std::move(comRdy.begin()->second);
            comRdy.erase(comRdy.begin());
            comsOut.push_back(std::move(completed));
        }
    }
    if ((comsOut.size() > 0) && (client))
    {
        std::lock_guard<std::mutex> csLock(mutCallback);
        while(!comsOut.empty())
        try
        {
            std::shared_ptr<CommandBase> completed = std::move(comsOut.front());
            client->Callback(static_cast<ICommand*>(completed.get()));
            comsOut.pop_front();
        } catch (...)
        {
            puts("Tinyt: Client-side raise in Callback routine.");
        }
    }
}

 
//Initialization
std::unique_ptr<Service> Service::instance { std::make_unique<Service>() };
