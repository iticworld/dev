#include "sync.hh"

namespace novemberizing { namespace concurrency {

Sync::Sync(void) : __mutex(nullptr), __mutexattr(nullptr)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Sync::~Sync(void)
{
    FUNCTION_START("");

    off();

    FUNCTION_END("");
}

int Sync::lock(void)
{
    FUNCTION_START("");
    int ret = Fail;
    if(__mutex!=nullptr)
    {
        if((ret = ::pthread_mutex_lock(__mutex))==Success)
        {
            DEBUG_LOG("succeed to ::pthread_mutex_lock(...)");
        }
        else
        {
            ERROR_LOG("fail to ::pthread_mutex_lock(...) caused by %d",ret);
        }
    }
    else
    {
        CAUTION_LOG("__mutex==nullptr");
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Sync::unlock(void)
{
    FUNCTION_START("");
    int ret = Fail;
    if(__mutex!=nullptr)
    {
        if((ret = ::pthread_mutex_unlock(__mutex))==Success)
        {
            DEBUG_LOG("succeed to ::pthread_mutex_unlock(...)");
        }
        else
        {
            ERROR_LOG("fail to ::pthread_mutex_unlock(...) caused by %d",ret);
        }
    }
    else
    {
        CAUTION_LOG("__mutex==nullptr");
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Sync::on(void)
{
    FUNCTION_START("");
    int ret = Fail;
    if(__mutex==nullptr)
    {
        __mutexattr = new pthread_mutexattr_t;
        ::memset(__mutexattr, 0, sizeof(pthread_mutexattr_t));
        ::pthread_mutexattr_init(__mutexattr);

        __mutex = new pthread_mutex_t;
        *__mutex = PTHREAD_MUTEX_INITIALIZER;
        if((ret = ::pthread_mutex_init(__mutex,__mutexattr))==Success)
        {
            DEBUG_LOG("succeed to ::pthread_mutex_init(...)");
        }
        else
        {
            ERROR_LOG("fail to ::pthread_mutex_init(...) caused by %d",ret);

            delete __mutex;
            __mutex = nullptr;

            ::pthread_mutexattr_destroy(__mutexattr);
            delete __mutexattr;
            __mutexattr = nullptr;
        }
    }
    else
    {
        NOTICE_LOG("__mutex!=nullptr");
        ret = Success;
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Sync::off(void)
{
    int ret = Fail;
    if(__mutex!=nullptr)
    {
        ::pthread_mutex_destroy(__mutex);
        delete __mutex;
        __mutex = nullptr;

        ::pthread_mutexattr_destroy(__mutexattr);
        delete __mutexattr;
        __mutexattr = nullptr;
    }
    else
    {
        NOTICE_LOG("__mutex==nullptr");
        ret = Success;
    }
    return ret==Success ? Success : Fail;
}

} }
