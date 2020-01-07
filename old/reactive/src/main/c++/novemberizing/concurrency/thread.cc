#include "thread.hh"

namespace novemberizing { namespace concurrency {

void * Thread::Routine(void * param)
{
    int ret = Fail;
    Thread * thread = static_cast<Thread *>(param);
    if(thread!=nullptr)
    {
        thread->run();
        ret = Success;
    }
    else
    {
        ERROR_LOG("thread==nullptr");
    }
    return reinterpret_cast<void *>(ret);
}

Thread::Thread(void) : __runnable(nullptr)
{
    FUNCTION_START("");

    ::memset(&__threadid, 0, sizeof(pthread_t));
    ::memset(&__threadattr, 0, sizeof(pthread_attr_t));

    FUNCTION_END("");
}

Thread::Thread(Runnable * runnable) : __runnable(runnable)
{
    FUNCTION_START("");

    ::memset(&__threadid, 0, sizeof(pthread_t));
    ::memset(&__threadattr, 0, sizeof(pthread_attr_t));

    FUNCTION_END("");
}

Thread::~Thread(void)
{
    FUNCTION_START("");

    stop();

    if(__runnable!=nullptr)
    {
        delete __runnable;
        __runnable = nullptr;
    }

    FUNCTION_END("");
}

void Thread::cancel(bool v)
{
    FUNCTION_START("");

    Cancellable::cancel(v);
    if(__runnable!=nullptr)
    {
        __runnable->cancel(v);
    }

    FUNCTION_END("");
}

bool Thread::alive(void)
{
    return __threadid!=0 && ::pthread_kill(__threadid, 0)==Success;
}

int Thread::start(void)
{
    FUNCTION_START("");
    int ret = Fail;
    if(alive()==false)
    {
        ::pthread_attr_init(&__threadattr);
        if((ret = ::pthread_create(&__threadid,&__threadattr, Thread::Routine, this))==Success)
        {
            DEBUG_LOG("succeed to ::pthread_create(...)");
        }
        else
        {
            ERROR_LOG("fail to ::pthread_create(...) caused by %d", ret);

            ::pthread_attr_destroy(&__threadattr);

            ::memset(&__threadid, 0, sizeof(pthread_t));
            ::memset(&__threadattr, 0, sizeof(pthread_attr_t));
        }
    }
    else
    {
        NOTICE_LOG("alive()==true");
        ret = Success;
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Thread::stop(void)
{
    FUNCTION_START("");
    int ret = Fail;
    if(alive())
    {
        cancel(true);
        void * r = nullptr;
        if((ret = ::pthread_join(__threadid, &r))==Success)
        {
            DEBUG_LOG("succeed to ::pthread_join(...) return %p",r);
        }
        else
        {
            ERROR_LOG("fail to ::pthread_join(...) caused by %d",ret);
        }
        ::pthread_attr_destroy(&__threadattr);

        ::memset(&__threadid, 0, sizeof(pthread_t));
        ::memset(&__threadattr, 0, sizeof(pthread_attr_t));
    }
    else
    {
        NOTICE_LOG("alive()==false");
        ret = Success;
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

} }
