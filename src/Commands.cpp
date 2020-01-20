#include <atomic>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <sstream>
#include <tuple>
#include "tsapi.h"
#include "server.h"
#include "command.h"

extern int verbose_flag;

CommandBase::CommandBase(Service *svc, int ttl)
{
    crTime = time(NULL);
    eolTime = crTime;
    comTTL = ttl;
    service = svc;
    id = svc->GenCommandId();
    executorId = 0;
    state = EState::New;
    moLink = nullptr;
}

CommandBase::~CommandBase()
{
    
}

void CommandBase::CltSideUp()
{
    bCltSideOn = true;
}

void CommandBase::Launch(time_t timeLaunch)
{
    eolTime = timeLaunch + comTTL;
}

void CommandBase::SetExecutor(int exId)
{
    executorId = exId;
    moLink = nullptr;
}
void CommandBase::SetState(EState st)
{
    state = st;
}

MoveableObject *CommandBase::Executor()
{
    if (!moLink)
        moLink = service->Mo(executorId);
    return moLink;
}

void CommandBase::Release()
{
    bCltSideOn = false;
}

RStatus CommandBase::AddCoords(int X, int Y)
{
    return RStatus::Unknown;
}

RStatus CommandBase::Invoke()
{
    state = EState::Refuse;
    return RStatus::Refuse;
}

///-----------------------MOVE
CommandMove::CommandMove(Service *svc, int ttl) : CommandBase(svc, ttl)
{
    ctr = 0;
}

CommandMove::~CommandMove()
{
    
}

RStatus CommandMove::AddCoords(int X, int Y)
{
    Realm *realm = service->World();
    PCell cell = realm->Cell(X, Y);
    if (!cell)
        return RStatus::Error;
    if (cell->Wall)
        return RStatus::Refuse;
    std::lock_guard<std::mutex> guard(mutDeque);
    points.push_back(std::make_tuple(X, Y));
    if (verbose_flag)
        printf("Tinyt: Command %d destination (%d, %d)\n", Id(), X, Y);
    return RStatus::Success;
}

//Multipoint movement routine;
RStatus CommandMove::Invoke()
{
    int Xdest, Ydest;
    int dx, dy, desX, desY;
    std::lock_guard<std::mutex> guard(mutDeque);
    if (points.empty())
    {
        state = EState::Refuse;
        return RStatus::Refuse;
    }
    std::tie(Xdest, Ydest) = points.front();
    if ((Xdest == Executor()->X) && (Ydest == Executor()->Y))
    {
        points.pop_front();
        if (points.empty())
        {
            state = EState::Success;
            return RStatus::Success;
        } 
        state = EState::Inproc;
        return RStatus::Async;
    }
    dx = dy = 0;
    if (Xdest > Executor()->X)
        dx = 1;
    if (Xdest < Executor()->X)
        dx = -1;
    if (Ydest > Executor()->Y)
        dy = 1;
    if (Ydest < Executor()->Y)
        dy = -1;
    desX = Executor()->X + dx;
    desY = Executor()->Y + dy;
    if (Check(Executor()->X + dx,  Executor()->Y + dy) != CheckCell::Free)
    {
        if (Check(Executor()->X + dx,  Executor()->Y) != CheckCell::Free)
        {
            desX = Executor()->X;
            desY = Executor()->Y - 1;
        }
        if (Check(Executor()->X,  Executor()->Y + dy) != CheckCell::Free)
        {
            desY = Executor()->Y;
            desX = Executor()->X - 1;
        }
    }
    Executor()->X = desX;
    Executor()->Y = desY;
    ctr++;
    if (ctr > 250)
    {
        state = EState::Refuse;
        return RStatus::Refuse;
    }
    
    if (verbose_flag)
    {
        std::stringstream ssInfo;
        ssInfo << "Object #" << Executor()->Id << " move to (" << desX << ", " << desY << ") stage " << ctr << ", DX = " << dx <<", DY = " << dy <<std::endl;
        std::cout << ssInfo.str();
    }
    
   return RStatus::Async;
}

CheckCell CommandMove::Check(int x, int y)
{
    PCell cell = service->World()->Cell(x, y);
    if (!cell)
        return CheckCell::Emptyness;
    if (cell->Wall)
        return CheckCell::Wall;
    return CheckCell::Free;
}

///-----------------------TEST
CommandTest::CommandTest(Service *svc, int ttl) : CommandBase(svc, ttl)
{
    ctr = 0;   
}

CommandTest::~CommandTest()
{
}

RStatus CommandTest::Invoke()
{
    RStatus rv = RStatus::Success;
    if (ctr > 0)
    {
        //std::stringstream ssInfo;
        //ssInfo << "Invoke Call #" << Id() << ", Stage " << ctr << ", Thr: " << std::this_thread::get_id() << std::endl;
        //std::cout << ssInfo.str();
        state = EState::Inproc;
        rv = RStatus::Async;
        ctr--;
    } 
   return rv;
}
