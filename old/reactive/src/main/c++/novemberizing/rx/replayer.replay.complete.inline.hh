#ifndef   __NOVEMBERIZING_RX__REPLAYER__REPLAY__COMPLETE__INLINE__HH__
#define   __NOVEMBERIZING_RX__REPLAYER__REPLAY__COMPLETE__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Replayer<T>::Replay::Complete::Complete(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Replayer<T>::Replay::Complete::~Complete(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::Replay::Complete::on(Observer<T> * observer)
{
    FUNCTION_START("");

    observer->onComplete();

    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__REPLAYER__REPLAY__COMPLETE__INLINE__HH__
