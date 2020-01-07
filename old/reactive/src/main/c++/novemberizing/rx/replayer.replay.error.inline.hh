#ifndef   __NOVEMBERIZING_RX__REPLAYER__REPLAY__ERROR__INLINE__HH__
#define   __NOVEMBERIZING_RX__REPLAYER__REPLAY__ERROR__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Replayer<T>::Replay::Error::Error(const Throwable & e) : __exception(e)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Replayer<T>::Replay::Error::~Error(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::Replay::Error::on(Observer<T> * observer)
{
    FUNCTION_START("");

    observer->onError(__exception);

    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__REPLAYER__REPLAY__ERROR__INLINE__HH__
