#ifndef   __NOVEMBERIZING_RX_SCHEDULERS__LOCAL__HH__
#define   __NOVEMBERIZING_RX_SCHEDULERS__LOCAL__HH__

#include <novemberizing/ds/cyclable.hh>
#include <novemberizing/ds/concurrent.list.hh>
#include <novemberizing/ds/concurrent.set.hh>

#include <novemberizing/concurrency/sync.hh>
#include <novemberizing/concurrency/thread.hh>

#include <novemberizing/rx/scheduler.hh>

namespace novemberizing { namespace rx { namespace schedulers {

using namespace concurrency;

class Local : public Scheduler
{
private:    static Thread::Local<Scheduler *> __schedulers;
public:     static Scheduler * Get(void);
private:    ConcurrentList<Executable *, Sync> __deletes;
private:    ConcurrentList<Executable *> __q;
private:    ConcurrentSet<Executable *> __executables;
public:     virtual void dispatch(Executable * executable);
public:     virtual void dispatch(std::initializer_list<Executable *> executables);
public:     virtual void completed(Executable * executable);
public:     virtual void executed(Executable * executable);
public:     virtual int run(void);
public:     Local(void);
public:     virtual ~Local(void);
};

} } }

#endif // __NOVEMBERIZING_RX_SCHEDULERS__LOCAL__HH__
