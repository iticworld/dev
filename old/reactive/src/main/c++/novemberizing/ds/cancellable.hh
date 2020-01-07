#ifndef   __NOVEMBERIZING_DS__CANCELLABLE__HH__
#define   __NOVEMBERIZING_DS__CANCELLABLE__HH__

#include <novemberizing/util/log.hh>

namespace novemberizing { namespace ds {

class Cancellable
{
protected:  bool __cancel;
public:     virtual void cancel(bool v);
public:     virtual bool cancel(void) const;
public:     Cancellable(void);
public:     virtual ~Cancellable(void);
};

} }

#endif // __NOVEMBERIZING_DS__CANCELLABLE__HH__
