#pragma once
#include <atomic>
#include <deque>
#include <tuple>
#include <sys/time.h>

enum class ExecutionEnum {Async, Immediate};

enum class CheckCell {Free, Wall, Emptyness};

class Service;
class CommandBase: public ICommand
{
public:
    CommandBase(Service *svc, int ttl);
    ~CommandBase() = default;
    virtual ExecutionEnum ExecutionType() const {return ExecutionEnum::Immediate;};
    time_t Eol() const {return eolTime;}
    bool CltSide() const {return bCltSideOn;}
    void Launch(time_t timeLaunch);
    int ExecutorId() const {return executorId;}
    virtual RStatus Invoke();
    
    void CltSideUp();
    void SetExecutor(int exId);
    void SetState(EState st);
    MoveableObject *Executor();
    
    //API
    virtual int Id() {return id;}
    virtual void Release();
    virtual EState State() {return state;};
    virtual RStatus AddCoords(int X, int Y);
    
    
protected:
    std::atomic<EState> state;
    time_t crTime, eolTime;
    Service *service;
    std::atomic_bool bCltSideOn;
    MoveableObject *moLink;
    int executorId;
private:
    int id;
    int comTTL;
};

class CommandMove: public CommandBase
{
public:
    CommandMove(Service *svc, int ttl);
    virtual ~CommandMove();
    virtual ExecutionEnum ExecutionType() const {return ExecutionEnum::Async;};
    virtual RStatus AddCoords(int X, int Y);
    virtual RStatus Invoke();
protected:
    std::deque<std::tuple<int, int>> points;
    std::mutex mutDeque;
    int ctr;
private:
    CheckCell Check(int x, int y);
};

class CommandTest: public CommandBase
{
public:
    CommandTest(Service *svc, int ttl);
    virtual ~CommandTest();
    virtual ExecutionEnum ExecutionType() const {return ExecutionEnum::Async;};
    virtual RStatus Invoke();
private:
    int ctr;
};