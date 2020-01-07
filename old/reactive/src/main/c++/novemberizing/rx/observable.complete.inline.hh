#ifndef   __NOVEMBERIZING_RX__OBSERVABLE_COMPLETE__INLINE__HH__
#define   __NOVEMBERIZING_RX__OBSERVABLE_COMPLETE__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Observable<T>::Complete::Complete(Observable<T> * observable) : __observable(observable)
{
    FUNCTION_START("");
    FUNCTION_END("");
}


template <class T>
Observable<T>::Complete::~Complete(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Observable<T>::Complete::execute(void)
{
    FUNCTION_START("");
    synchronized(__observable, {
        __replayers.complete();
        __observable->__complete();
    });
    __executor->completed(this);
    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__OBSERVABLE_COMPLETE__INLINE__HH__
