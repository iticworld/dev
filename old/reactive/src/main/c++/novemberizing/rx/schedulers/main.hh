#ifndef   __NOVEMBERIZING_RX_SCHEDULERS__MAIN__HH__
#define   __NOVEMBERIZING_RX_SCHEDULERS__MAIN__HH__

#include <novemberizing/ds/cyclable.hh>
#include <novemberizing/ds/concurrent.list.hh>
#include <novemberizing/ds/concurrent.set.hh>
#include <novemberizing/ds/concurrent.linked.set.hh>

#include <novemberizing/concurrency/sync.hh>

#include <novemberizing/rx/scheduler.hh>

namespace novemberizing { namespace rx { namespace schedulers {

using namespace ds;
using namespace concurrency;

class Main : public Scheduler, public Sync
{
private:    static Main * __singleton;
public:     static Main * Get(void);
private:    ConcurrentList<Executable *, Sync> __deletes;
private:    ConcurrentList<Executable *> __q;
private:    ConcurrentSet<Executable *> __executables;
private:    ConcurrentLinkedSet<Cyclable *> __cyclables;
public:     virtual void add(Cyclable * cyclable);
public:     virtual void dispatch(Executable * executable);
public:     virtual void dispatch(std::initializer_list<Executable *> executables);
public:     virtual void completed(Executable * executable);
public:     virtual void executed(Executable * executable);
public:     virtual int run(void);
private:    Main(void);
public:     virtual ~Main(void);
};

} } }

#endif // __NOVEMBERIZING_RX_SCHEDULERS__MAIN__HH__
