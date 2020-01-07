#ifndef   __NOVEMBERIZING_RX__SCHEDULER__HH__
#define   __NOVEMBERIZING_RX__SCHEDULER__HH__

#include <novemberizing/ds/executor.hh>
#include <novemberizing/ds/executable.hh>
#include <novemberizing/ds/runnable.hh>

namespace novemberizing { namespace rx {

using namespace ds;

class Scheduler : public Executor, public Runnable
{
public:     static Scheduler * Main(void);
public:     static Scheduler * Self(void);
public:     static Scheduler * Local(void);
public:     static Scheduler * Get(void);
public:     Scheduler(void);
public:     virtual ~Scheduler(void);
};

} }

#endif // __NOVEMBERIZING_RX__SCHEDULER__HH__
