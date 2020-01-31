#pragma once

enum class RStatus {Unknown, Error, Success, Refuse, Async};
enum class EState {Unknown, New, Inproc, Success, Refuse, Timeout};
enum class Action {Move, Test};


class ICommand 
{
public:
    virtual int Id() = 0;
    virtual void Release() = 0;
    virtual EState State() = 0;
    virtual RStatus AddCoords(int X, int Y) = 0;
};

class ICallback
{
public:
    virtual void Callback(ICommand *command) = 0;
};

class IServer 
{
public:
    virtual RStatus CreateCommand(Action action, int executorId, int toutSec, ICommand **coRef) = 0;
    virtual RStatus CreateMoveable(int desireX, int desireY, int &moId) = 0;
    virtual RStatus GetDimSize(int &capX, int &capY) = 0;
    virtual RStatus ExecuteCommand(int commId) = 0;
    virtual void CallbackSet(ICallback *intrfc) = 0;
    virtual void CallbackClear() = 0;
};



IServer *EntryPoint();