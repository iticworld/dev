#ifndef   __NOVEMBERIZING_DS__RUNNABLE__HH__
#define   __NOVEMBERIZING_DS__RUNNABLE__HH__

#include <novemberizing/ds/cancellable.hh>

namespace novemberizing { namespace ds {

class Runnable : public Cancellable
{
public:     virtual int run(void) = 0;
public:     inline Runnable(void);
public:     inline virtual ~Runnable(void);
};

} }

#include <novemberizing/ds/runnable.inline.hh>

#endif // __NOVEMBERIZING_DS__RUNNABLE__HH__
