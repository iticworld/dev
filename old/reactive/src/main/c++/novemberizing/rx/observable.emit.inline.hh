#ifndef   __NOVEMBERIZING_RX__OBSERVABLE_EMIT__INLINIE__HH__
#define   __NOVEMBERIZING_RX__OBSERVABLE_EMIT__INLINIE__HH__

namespace novemberizing { namespace rx {

template <class T>
Observable<T>::Emit::Emit(Observable<T> * observable, const T & v) : __observable(observable), __value(v)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Observable<T>::Emit::~Emit(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
const T & Observable<T>::Emit::in(void) const
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __value;
}

template <class T>
void Observable<T>::Emit::execute(void)
{
    FUNCTION_START("");
    synchronized(__observable, {
        __replayers.emit(in());
        __observable->__emit(in());
    });
    __executor->completed(this);
    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__OBSERVABLE_EMIT__INLINIE__HH__
