#ifndef   __NOVEMBERIZING_RX__SUBSCRIBERS__JUST__HH__
#define   __NOVEMBERIZING_RX__SUBSCRIBERS__JUST__HH__

#include <string>
#include <iostream>

#include <novemberizing/rx/observer.hh>

namespace novemberizing { namespace rx { namespace subscribers {

template <class T>
class Just : public Observer<T>
{
private:    std::string __tag;
protected:  virtual void onNext(const T & item);
protected:  virtual void onError(const Throwable & exception);
protected:  virtual void onComplete(void);
public:     Just(void);
public:     Just(const std::string & tag);
public:     Just(std::string && tag);
public:     virtual ~Just(void);
};

} } }

#include <novemberizing/rx/subscribers/just.inline.hh>

#endif // __NOVEMBERIZING_RX__SUBSCRIBERS__JUST__HH__
