#ifndef   __NOVEMBERIZING_DS__EXECUTABLE__HH__
#define   __NOVEMBERIZING_DS__EXECUTABLE__HH__

#include <novemberizing/ds/executor.hh>

namespace novemberizing { namespace ds {

class Executable
{
protected:  Executor * __executor;
public:     virtual void execute(Executor * executor);
public:     virtual void execute(void) = 0;
public:     Executable(void);
public:     virtual ~Executable(void);
};

} }

#endif // __NOVEMBERIZING_DS__EXECUTABLE__HH__
