#ifndef   __NOVEMBERIZING_CONCURRENCY__CONDITION__HH__
#define   __NOVEMBERIZING_CONCURRENCY__CONDITION__HH__

#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace concurrency {

class Condition : public Sync
{
protected:  pthread_cond_t * __cond;
protected:  pthread_condattr_t * __condattr;
public:     virtual int on(void);
public:     virtual int off(void);
public:     virtual int suspend(type::nano nano = Infinite);
public:     virtual int resume(bool all = false);
public:     Condition(void);
public:     virtual ~Condition(void);
};

} }

#endif // __NOVEMBERIZING_CONCURRENCY__CONDITION__HH__
