#ifndef   __NOVEMBERIZING_RX__TASK__HH__
#define   __NOVEMBERIZING_RX__TASK__HH__

#include <novemberizing/ds/executable.hh>

namespace novemberizing { namespace rx {

using namespace ds;

class Task : public Executable
{
public:     Task(void);
public:     virtual ~Task(void);
};

} }

#include <novemberizing/rx/task.inline.hh>

#endif // __NOVEMBERIZING_RX__TASK__HH__
