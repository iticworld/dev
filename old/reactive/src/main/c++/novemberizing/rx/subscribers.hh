#ifndef   __NOVEMBERIZING_RX__SUBSCRIBERS__HH__
#define   __NOVEMBERIZING_RX__SUBSCRIBERS__HH__

#include <novemberizing/rx/observer.hh>
#include <novemberizing/rx/subscribers/just.hh>

namespace novemberizing { namespace rx {

class Subscribers
{
public:     template <class T> static Observer<T> * Just(void);
public:     template <class T> static Observer<T> * Just(const std::string & tag);
public:     template <class T> static Observer<T> * Just(std::string && tag);
public:     Subscribers(void);
public:     virtual ~Subscribers(void);
};

} }

#include <novemberizing/rx/subscribers.inline.hh>

#endif // __NOVEMBERIZING_RX__SUBSCRIBERS__HH__
