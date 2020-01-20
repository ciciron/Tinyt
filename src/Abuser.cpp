#include <algorithm>
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include "abuser.h"

extern int verbose_flag;
extern int test_flag;

//Main client impl

Client::Client(IServer *inst): Abuser(inst)
{
    memIndx = 0;
}

bool Client::DoAbuse(int numComms)
{
    std::future<void> computeComplete = complete.get_future();
    int ctrSuccess, ctrRefuse, ctrOther, ctrReturned;
    auto moIterator = molist.begin();
    if (moIterator == molist.end())
    {
        puts("Tinyt: No objects for abuse.");
        return true;
    }
    memIndx = 0;
    memory.reserve(numComms); //array 4-wr without mutex
    service->CallbackSet(static_cast<ICallback*>(this));
    for (int numCo = 0; numCo < numComms; numCo++)
    {
        const int cstToutSec = 30;
        ICommand *co;
        int moNumber = moIterator->moId;
        if (RStatus::Success == service->CreateCommand(Action::Move, moNumber, cstToutSec, &co))
        {
            std::uniform_int_distribution<> X(0, rangeX-1);
            std::uniform_int_distribution<> Y(0, rangeY-1);
            moIterator->mem.push_back(std::make_tuple(co->Id(), co->State()));
            while (RStatus::Refuse == co->AddCoords(X(gen), Y(gen)));
            co->Release();
        }
        if(++moIterator == molist.end())
            moIterator = molist.begin();
    } 
    for (auto it = molist.begin(); it != molist.end(); ++it)
    {
        int commandId = std::get<0>(it->mem.front());
        RStatus status = service->ExecuteCommand(commandId);
        if (verbose_flag)
        switch (status)
        {
            case RStatus::Async:
                printf("Tinyt: Command #%d launched async.\n", commandId); 
                break;
            case RStatus::Success:
                printf("Tinyt: Command #%d success.\n", commandId); 
                break;            
            case RStatus::Refuse:
                printf("Tinyt: Command #%d refuse.\n", commandId); 
                break; 
            default:
                printf("Tinyt: Command #%d unknown launch status.\n", commandId); 
                break;
        }
    }
    //computeComplete.wait_for(std::chrono::seconds(5));
    computeComplete.wait();
    
    service->CallbackClear();
    ctrSuccess = ctrRefuse = ctrOther = ctrReturned = 0;
    for (size_t sz = 0; sz < memIndx; sz++)
    {
        if (memory[sz].returned)
            ctrReturned++;
        if (memory[sz].state == EState::Success)
            ctrSuccess++;
        else if (memory[sz].state == EState::Refuse)
            ctrRefuse++;
        else
            ctrOther++;
    }
    printf("Total commands %d(sended)/%d(rcv)\n", numComms, ctrReturned);
    printf("Success: %d\n", ctrSuccess);
    printf("Refuse: %d\n", ctrRefuse);
    printf("Other: %d\n", ctrOther);
    
    
    return true; 
}

void Client::Callback(ICommand *command)
{
    AsyncMemory *area;
    bool bAllComplete = true;
    area = memory.data();
    for (auto it = molist.begin(); it != molist.end(); ++it)
    {
        if (!it->mem.empty())
        {
            if (std::get<0>(it->mem.front()) == command->Id())
            {
                area[memIndx].comId = std::get<0>(it->mem.front());
                area[memIndx].state = command->State();
                area[memIndx++].returned = true;
                it->mem.pop_front();
                if (!it->mem.empty())
                    service->ExecuteCommand(std::get<0>(it->mem.front()));
            }
        }
        bAllComplete &= it->mem.empty();
    }
    if (bAllComplete)
        complete.set_value();
}

Abuser::Abuser(IServer *inst)
{
    rangeX = 0;
    rangeY = 0;
    service = inst;
    service->GetDimSize(rangeX, rangeY);
}

bool Abuser::Add(int desireX, int desireY)
{
    int moElementId;
    RStatus rvCrt;
    std::lock_guard<std::mutex> lock(mutObjs);  
    rvCrt = service->CreateMoveable(desireX, desireY, moElementId);
    molist.push_back({moElementId});
    return rvCrt == RStatus::Success;
}

void Abuser::Callback(ICommand *command)
{
    std::lock_guard<std::mutex> csLock(consoleMan);
    if (command)
    {
        printf("Tinyt: Command complete #%d (clt side).\n", command->Id());
    } else
        puts("Tinyt: Callback with null-point reference.");
}

//Simple (test) client impl

Simple::Simple(IServer *inst):Abuser(inst)
{
   if (verbose_flag)
   {
       puts("Tinyt: Simple abuser class was created.");
   }
}

bool Simple::DoAbuse(int numComms)
{
    service->CallbackSet(static_cast<ICallback*>(this));
    ICommand *co;
    for (int numCo = 0; numCo < numComms; numCo++)
    if (RStatus::Success == service->CreateCommand(Action::Test, numCo, 30, &co))
    {
        int commandId = co->Id();
        RStatus status = service->ExecuteCommand(commandId);
        co->Release();
        if (status == RStatus::Async)
        {
           printf("Tinyt: Command #%d launched async.\n", commandId); 
        }
    }
    /*
    for (int numCo = 0; numCo < numComms; numCo++)
    if (RStatus::Success == service->CreateCommand(Action::Move, numCo, 30, &co))
    {
        int commandId = co->Id();
        co->AddCoords(95,138);
        RStatus status = service->ExecuteCommand(commandId);
        co->Release();
        if (status == RStatus::Async)
        {
           printf("Tinyt: Command #%d launched async.\n", commandId); 
        }
    }*/
    std::this_thread::sleep_for(std::chrono::seconds(3));
    service->CallbackClear();
    return true; 
}

//Static instance generator
std::unique_ptr<Abuser> Abuser::Create(IServer *inst, int numbers)
{
    std::unique_ptr<Abuser> rv;
    try
    {
        if (test_flag)
            rv = std::make_unique<Simple>(inst);
        else
            rv = std::make_unique<Client>(inst);
    } catch(...)
    {
        if (verbose_flag)
            puts("Tinyt: Cannot create client service(except).");
        return nullptr;
    }
    for (int idx = 0; idx < numbers; idx++)
    {
        std::uniform_int_distribution<> distrX(0, rv->rangeX-1);
        std::uniform_int_distribution<> distrY(0, rv->rangeY-1);
        int desX, desY;
        desX = distrX(gen);
        desY = distrY(gen);
        if (!rv->Add(desX, desY))
        {
            puts("Tinyt: Cannot add moveable object(s).");
            break;
        }
    }
    return rv;
}

std::mt19937 Abuser::gen {0};