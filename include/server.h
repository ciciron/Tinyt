#pragma once
#include <atomic>
#include <condition_variable>
#include <deque>
#include <future>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <sys/time.h>
#include "realm.h"

//Service - command executor.

//struct WorkerState
//{
 //   std::promise<void> term;
 //   std::thread thr;
//};

class CommandBase;

class Service: public IServer {
public:
    static Service *EntryPoint();
    Service();
    ~Service();
    int GenCommandId();
    Realm* World() const {return realm.get();};
    MoveableObject *Mo(int number);
    
    //API
    virtual RStatus CreateCommand(Action action, int executorId, int toutSec, ICommand **coRef);
    virtual RStatus CreateMoveable(int desireX, int desireY, int &botId);
    virtual RStatus GetDimSize(int &capX, int &capY);
    virtual RStatus ExecuteCommand(int commId);
    virtual void CallbackSet(ICallback *intrfc);
    virtual void CallbackClear();    
    
private: 
    RStatus Launch(CommandBase *comBase);
    RStatus Exec(CommandBase *comBase);
    size_t Worker();
    void NotifyClient(int size_t);

    static std::unique_ptr<Service> instance;
    std::unique_ptr<Realm> realm;
    
    std::mutex mutObjects;
    std::map<int, std::unique_ptr<MoveableObject>> objects;
    
    std::mutex mutcstore;
    std::map<int, std::shared_ptr<CommandBase>> comStore;  //New commands
    std::map<int, std::shared_ptr<CommandBase>> comInproc; //Inprocess commands
    std::map<int, std::shared_ptr<CommandBase>> comRdy;    //Ready(completed) commands
    std::deque<CommandBase*> comQue;
    
    std::mutex mutCallback;
    ICallback *client;
    
    std::atomic<int> objEnumerator;
    std::atomic<int> comEnumerator;
    
    std::list<std::thread> thrds;
    
    std::promise<void> promTerm;
    std::shared_future<void> term;
    std::condition_variable queNotify;
};