#ifndef   __NOVEMBERIZING_CONCURRENCY__THREAD__LOCAL__INLINE__HH__
#define   __NOVEMBERIZING_CONCURRENCY__THREAD__LOCAL__INLINE__HH__

#include <novemberizing/concurrency/thread.hh>

namespace novemberizing { namespace concurrency {

template <class T>
inline void Thread::Local<T>::Destructor(void * p)
{
    FUNCTION_START("");
    T v = static_cast<T>(p);
    if(v!=nullptr)
    {
        delete v;
    }
    else
    {
        WARNING_LOG("static_cast<T>(p)==nullptr");
    }
    FUNCTION_END("");
}

template <class T>
inline Thread::Local<T>::Local(void)
{
    FUNCTION_START("");

    ::memset(&__key, 0, sizeof(pthread_key_t));

    int ret = Success;
    if((ret = ::pthread_key_create(&__key, Thread::Local<T>::Destructor))==Success)
    {
        DEBUG_LOG("succeed to ::pthread_key_create(...)");
    }
    else
    {
        ERROR_LOG("fail to ::pthread_key_create(...) caused by %d",ret);
    }

    FUNCTION_END("");
}

template <class T>
inline Thread::Local<T>::~Local(void)
{
    FUNCTION_START("");

    int ret = ::pthread_key_delete(__key);
    if(ret==Success)
    {
        DEBUG_LOG("succeed to ::pthread_key_delete(...)");
    }
    else
    {
        ERROR_LOG("fail to ::pthread_key_delete(...) caused by %d",ret);
    }

    FUNCTION_END("");
}

template <class T>
inline T Thread::Local<T>::get(void)
{
    return reinterpret_cast<T>(pthread_getspecific(__key));
}

template <class T>
inline void Thread::Local<T>::set(const T & v)
{
    T o = get();
    if(o!=nullptr){ Thread::Local<T>::Destructor(o); }
    pthread_setspecific(__key, v);
}

} }

#endif // __NOVEMBERIZING_CONCURRENCY__THREAD__LOCAL__INLINE__HH__
