#ifndef   __NOVEMBERIZING_RX__OBSERVER__HH__
#define   __NOVEMBERIZING_RX__OBSERVER__HH__

#include <novemberizing/util/log.hh>

#include <novemberizing/ds/throwable.hh>
#include <novemberizing/ds/concurrent.set.hh>

namespace novemberizing { namespace rx {

using namespace ds;
using namespace concurrency;

template <class T> class Observable;
template <class T> class Replayer;

template <class T>
class Observer : public Sync
{
private:    ConcurrentSet<Observable<T>*> __observables;
protected:  virtual void onNext(const T & item) = 0;
protected:  virtual void onError(const Throwable & exception) = 0;
protected:  virtual void onComplete(void) = 0;
public:     virtual void onSubscribe(Observable<T> * observable);
public:     virtual void onUnsubscribe(Observable<T> * observable);
public:     Observer(void);
public:     virtual ~Observer(void);
public:     friend class Observable<T>;
public:     friend class Replayer<T>;
};

} }

#include <novemberizing/rx/observer.inline.hh>

#endif // __NOVEMBERIZING_RX__OBSERVER__HH__
