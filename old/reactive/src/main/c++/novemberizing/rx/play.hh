#ifndef   __NOVEMBERIZING_RX__PLAY__HH__
#define   __NOVEMBERIZING_RX__PLAY__HH__

#include <novemberizing/rx/observer.hh>
#include <novemberizing/rx/emittable.hh>

namespace novemberizing { namespace rx {

template <class T>
class Play
{
public:     virtual void on(Observer<T> * observer) = 0;
public:     Play(void);
public:     virtual ~Play(void);
};

} }

#include <novemberizing/rx/play.inline.hh>

#endif // __NOVEMBERIZING_RX__PLAY__HH__
