#include "condition.hh"

namespace novemberizing { namespace concurrency {

Condition::Condition(void) : __cond(nullptr), __condattr(nullptr)
{
    FUNCTION_START("");

    FUNCTION_END("");
}

Condition::~Condition(void)
{
    FUNCTION_START("");

    off();

    FUNCTION_END("");
}

int Condition::on(void)
{
    FUNCTION_START("");

    int ret = Fail;
    if((ret=Sync::on())==Success)
    {
        if(__cond==nullptr)
        {
            __condattr = new pthread_condattr_t;
            ::memset(__condattr, 0, sizeof(pthread_condattr_t));
            ::pthread_condattr_init(__condattr);

            __cond = new pthread_cond_t;
            *__cond = PTHREAD_COND_INITIALIZER;

            if((ret = ::pthread_cond_init(__cond, __condattr))==Success)
            {
                DEBUG_LOG("succeed to ::pthread_cond_init(...)");
            }
            else
            {
                ERROR_LOG("fail to ::pthread_cond_init(...) caused by %d",ret);

                ::pthread_condattr_destroy(__condattr);
                delete __condattr;
                __condattr = nullptr;

                delete __cond;
                __cond = nullptr;
            }
        }
        else
        {
            NOTICE_LOG("__cond!=nullptr");
            ret = Success;
        }
    }
    else
    {
        ERROR_LOG("fail to Sync::on()");

        if(__cond!=nullptr)
        {
            ::pthread_cond_destroy(__cond);
            delete __cond;
            __cond = nullptr;
        }

        if(__condattr!=nullptr)
        {
            ::pthread_condattr_destroy(__condattr);
            delete __condattr;
            __condattr = nullptr;
        }
    }

    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Condition::off(void)
{
    FUNCTION_START("");
    if(__cond!=nullptr)
    {
        ::pthread_cond_destroy(__cond);
        delete __cond;
        __cond = nullptr;

        ::pthread_condattr_destroy(__condattr);
        delete __condattr;
        __condattr = nullptr;
    }
    else
    {
        NOTICE_LOG("__cond==nullptr");
    }
    FUNCTION_END("");
    return Sync::off();
}

int Condition::suspend(type::nano nano)
{
    FUNCTION_START("");
    int ret = Fail;
    if(__cond!=nullptr)
    {
        if(nano==Infinite)
        {
            if((ret = ::pthread_cond_wait(__cond, __mutex))==Success)
            {
                DEBUG_LOG("succeed to ::pthread_cond_wait(...)");
            }
            else
            {
                ERROR_LOG("fail to ::pthread_cond_wait(...) caused by %d",ret);
            }
        }
        else
        {
            struct timespec spec;
            clock_gettime(CLOCK_REALTIME, &spec);
            spec.tv_nsec = nano%1000000000;
            spec.tv_sec = nano/1000000000 + spec.tv_nsec/1000000000;
            if((ret = ::pthread_cond_timedwait(__cond, __mutex, &spec))==Success)
            {
                DEBUG_LOG("succeed to ::pthread_cond_timedwait(...)");
            }
            else
            {
                ERROR_LOG("fail to ::pthread_cond_timedwait(...) caused by %d",ret);
            }
        }
    }
    else
    {
        CAUTION_LOG("__cond==nullptr");
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

int Condition::resume(bool all)
{
    FUNCTION_START("");
    int ret = Fail;
    if(__cond!=nullptr)
    {
        if(all)
        {
            if((ret = ::pthread_cond_broadcast(__cond))==Success)
            {
                DEBUG_LOG("succeed to ::pthread_cond_broadcast(...)");
            }
            else
            {
                ERROR_LOG("fail to ::pthread_cond_broadcast(...) caused by %d",ret);
            }
        }
        else
        {
            if((ret = ::pthread_cond_signal(__cond))==Success)
            {
                DEBUG_LOG("succeed to ::pthread_cond_signal(...)");
            }
            else
            {
                ERROR_LOG("fail to ::pthread_cond_signal(...) caused by %d",ret);
            }
        }
    }
    else
    {
        CAUTION_LOG("__cond==nullptr");
    }
    FUNCTION_END("");
    return ret==Success ? Success : Fail;
}

} }
