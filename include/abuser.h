#include <atomic>
#include <deque>
#include <future>
#include <list>
#include <memory>
#include <mutex>
#include <tuple>
#include <random>
#include <vector>
#include "tsapi.h"

struct AsyncMemory
{
    int comId;
    EState state;
    bool returned;
};

struct Modetu //M.O. + deque + tuple
{   //one command can be executed at once
    Modetu() = delete;
    int moId;
    std::deque<std::tuple<int, EState>> mem;
};

class Abuser: public ICallback
{
public:
    static std::unique_ptr<Abuser> Create(IServer *inst, int numbers);
    Abuser(IServer *inst);
    virtual ~Abuser() {};
    virtual bool DoAbuse(int numComms) = 0;
    virtual void Callback(ICommand *command);
    
protected:
    bool Add(int desireX, int desireY);
    
    std::mutex mutObjs;
    std::list<Modetu> molist;
    IServer *service;
    int rangeX, rangeY;
    static std::mt19937 gen;
    std::mutex consoleMan;
};

//Main abuser
class Client: public Abuser
{
public:
    Client(IServer *inst);
    virtual ~Client() {};
    virtual bool DoAbuse(int numComms);
    virtual void Callback(ICommand *command);
private:
    std::vector<AsyncMemory> memory; 
    std::atomic<size_t> memIndx;
    std::promise<void> complete;
};

//Test abuser
class Simple: public Abuser
{
public:
    Simple(IServer *inst);
    virtual ~Simple() {};
    virtual bool DoAbuse(int numComms);
};