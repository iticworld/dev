#ifndef   __NOVEMBERIZING_RX__OBSERVABLE_ERROR__INLINE__HH__
#define   __NOVEMBERIZING_RX__OBSERVABLE_ERROR__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Observable<T>::Error::Error(Observable<T> * observable, const Throwable & v) : Task(v), __observable(observable)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Observable<T>::Error::~Error(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Observable<T>::Error::execute(void)
{
    FUNCTION_START("");
    synchronized(__observable, {
        __replayers.emit(exception());
        __observable->__emit(exception());
    });
    __executor->completed(this);
    FUNCTION_END("");
}

template <class T>
const Throwable & Observable<T>::Error::exception(void) const
{
    return __exception;
}

} }

#endif // __NOVEMBERIZING_RX__OBSERVABLE_ERROR__INLINE__HH__
