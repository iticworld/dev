#ifndef   __NOVEMBERIZING_RX__EMITTABLE__HH__
#define   __NOVEMBERIZING_RX__EMITTABLE__HH__

#include <novemberizing/util/log.hh>

#include <novemberizing/ds/throwable.hh>
#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace rx {

using namespace ds;
using namespace concurrency;

template <class T>
class Emittable
{
protected:  virtual void emit(const T & item) = 0;
protected:  virtual void error(const Throwable & exception) = 0;
protected:  virtual void complete(void) = 0;
public:     Emittable(void);
public:     virtual ~Emittable(void);
};

} }

#include <novemberizing/rx/emittable.inline.hh>

#endif // __NOVEMBERIZING_RX__EMITTABLE__HH__
