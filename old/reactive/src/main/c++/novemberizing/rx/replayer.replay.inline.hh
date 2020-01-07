#ifndef   __NOVEMBERIZING_RX__REPLAYER__REPLAY__INLINE__HH__
#define   __NOVEMBERIZING_RX__REPLAYER__REPLAY__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Replayer<T>::Replay::Replay(const T & item) : __item(item)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Replayer<T>::Replay::~Replay(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::Replay::on(Observer<T> * observer)
{
    FUNCTION_START("");

    observer->onNext(__item);

    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__REPLAYER__REPLAY__INLINE__HH__
