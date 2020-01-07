#ifndef   __NOVEMBERIZING_RX__OBSERVER__INLINE__HH__
#define   __NOVEMBERIZING_RX__OBSERVER__INLINE__HH__

#include <novemberizing/rx/observer.hh>

namespace novemberizing { namespace rx {

template <class T>
Observer<T>::Observer(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Observer<T>::~Observer(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Observer<T>::onSubscribe(Observable<T> * observable)
{
    FUNCTION_START("");
    synchronized(&__observables,__observables.add(observable));
    FUNCTION_END("");
}

template <class T>
void Observer<T>::onUnsubscribe(Observable<T> * observable)
{
    FUNCTION_START("");
    synchronized(&__observables,__observables.del(observable));
    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__OBSERVER__INLINE__HH__
