#include "local.hh"

namespace novemberizing { namespace rx { namespace schedulers {

Thread::Local<Scheduler *> Local::__schedulers;

Scheduler * Local::Get(void)
{
    Scheduler * scheduler = __schedulers.get();
    if(scheduler==nullptr)
    {
        __schedulers.set(scheduler=new Local());
    }
    return scheduler;
}

Local::Local(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Local::~Local(void)
{
    FUNCTION_START("");
    type::size remain = 0;
    do {
        __q.lock();
        while(__q.size()>0){
            __q.pop([this](Executable * executable){
                if(executable!=nullptr)
                {
                    __q.unlock();
                    synchronized(&__executables, __executables.add(executable));
                    executable->execute(this);
                    __q.lock();
                }
                else
                {
                    NOTICE_LOG("executable==nullptr");
                }
            });
        }
        synchronized(&__executables, remain = __executables.size());
        __q.unlock();
    } while(remain>0);
    synchronized(&__deletes,{
        while(__deletes.size()>0)
        {
            __deletes.pop([](Executable * executable){
                if(executable!=nullptr) {
                    delete executable;
                }
            });
        }
    });
    FUNCTION_END("");
}

int Local::run(void)
{
    while(!cancel()){
        __q.lock();
        type::size current = __q.size();
        for(type::size i = 0;i<current && __q.size()>0;i++)
        {
            __q.pop([this](Executable * executable){
                if(executable!=nullptr)
                {
                    __q.unlock();
                    synchronized(&__executables, __executables.add(executable));
                    executable->execute(this);
                    __q.lock();
                }
                else
                {
                    NOTICE_LOG("executable==nullptr");
                }
            });
        }
        __q.unlock();
        synchronized(&__deletes,{
            while(__deletes.size()>0)
            {
                __deletes.pop([](Executable * executable){
                    if(executable!=nullptr) {
                        delete executable;
                    }
                });
            }
        });
    }
    return Success;
}

void Local::dispatch(Executable * executable)
{
    FUNCTION_START("");
    synchronized(&__q,{
        if(executable!=nullptr){ __q.push(executable); }
        __q.resume();
    });
    FUNCTION_END("");
}

void Local::dispatch(std::initializer_list<Executable *> executables)
{
    FUNCTION_START("");
    synchronized(&__q,{
        for(std::initializer_list<Executable *>::iterator it = executables.begin();executables.end();it++)
        {
            if(*it!=nullptr){ __q.push(*it); }
        }
        __q.resume(true);
    });
    FUNCTION_END("");
}

void Local::completed(Executable * executable)
{
    FUNCTION_START("");
    if(executable!=nullptr)
    {
        synchronized(&__executables, __executables.del(executable));
    }
    FUNCTION_END("");
}

void Local::executed(Executable * executable)
{
    FUNCTION_START("");
    if(executable!=nullptr)
    {
        synchronized(&__executables, __executables.del(executable));
        synchronized(&__q, {
            __q.front(executable);
            __q.resume();
        });
    }
    FUNCTION_END("");
}

} } }
