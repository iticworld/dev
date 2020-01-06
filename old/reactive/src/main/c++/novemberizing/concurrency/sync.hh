#ifndef   __NOVEMBERIZING_CONCURRENCY__SYNC__HH__
#define   __NOVEMBERIZING_CONCURRENCY__SYNC__HH__

#include <pthread.h>
#include <string.h>

#include <novemberizing.hh>

#include <novemberizing/util/log.hh>

namespace novemberizing { namespace concurrency {

class Sync
{
protected:  pthread_mutex_t * __mutex;
protected:  pthread_mutexattr_t * __mutexattr;
public:     virtual int on(void);
public:     virtual int off(void);
public:     virtual int lock(void);
public:     virtual int unlock(void);
public:     Sync(void);
public:     virtual ~Sync(void);
};

} }

#define synchronized(sync, block) {                                                                         \
    novemberizing::concurrency::Sync * __sync__ = static_cast<novemberizing::concurrency::Sync *>(sync);    \
    if(__sync__!=nullptr){                                                                                  \
        __sync__->lock();                                                                                   \
        block;                                                                                              \
        __sync__->unlock();                                                                                 \
    }                                                                                                       \
}

#endif // __NOVEMBERIZING_CONCURRENCY__SYNC__HH__
