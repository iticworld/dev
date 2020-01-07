#ifndef   __NOVEMBERIZING_CONCURRENCY__THREAD__HH__
#define   __NOVEMBERIZING_CONCURRENCY__THREAD__HH__

#include <pthread.h>
#include <string.h>
#include <signal.h>

#include <novemberizing.hh>

#include <novemberizing/util/log.hh>

#include <novemberizing/ds/runnable.hh>

namespace novemberizing { namespace concurrency {

using namespace ds;

class Thread : public Runnable
{
            /**
             * http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_key_create.html
             */
public:     template <class T>
            class Local
            {
            public:     inline static void Destructor(void * p);
            private:    pthread_key_t __key;
            public:     inline T get(void);
            public:     inline void set(const T & v);
            public:     inline Local(void);
            public:     inline virtual ~Local(void);
            };
private:    static void * Routine(void * param);
private:    pthread_t __threadid;
private:    pthread_attr_t __threadattr;
private:    Runnable * __runnable;
public:     virtual void cancel(bool v);
public:     virtual bool alive(void);
public:     virtual int start(void);
public:     virtual int stop(void);
public:     Thread(void);
public:     Thread(Runnable * runnable);
public:     virtual ~Thread(void);
};

} }

#include <novemberizing/concurrency/thread.local.inline.hh>

#endif // __NOVEMBERIZING_CONCURRENCY__THREAD__HH__
