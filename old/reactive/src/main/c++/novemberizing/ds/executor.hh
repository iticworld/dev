#ifndef   __NOVEMBERIZING_DS__EXECUTOR__HH__
#define   __NOVEMBERIZING_DS__EXECUTOR__HH__

#include <initializer_list>

#include <novemberizing.hh>

#include <novemberizing/util/log.hh>

namespace novemberizing { namespace ds {

class Executable;

class Executor
{
public:     virtual void dispatch(Executable * executable) = 0;
public:     virtual void dispatch(std::initializer_list<Executable *> executables) = 0;
public:     virtual void completed(Executable * executable) = 0;
public:     virtual void executed(Executable * executable) = 0;
public:     Executor(void);
public:     virtual ~Executor(void);
};

} }

#endif // __NOVEMBERIZING_DS__EXECUTOR__HH__
