#ifndef   __NOVEMBERIZING_RX__SUBSCRIBERS__INLINE__HH__
#define   __NOVEMBERIZING_RX__SUBSCRIBERS__INLINE__HH__

namespace novemberizing { namespace rx {

Subscribers::Subscribers(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Subscribers::~Subscribers(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Observer<T> * Subscribers::Just(void)
{
    return new subscribers::Just<T>();
}

template <class T>
Observer<T> * Subscribers::Just(const std::string & tag)
{
    return new subscribers::Just<T>(tag);
}

template <class T>
Observer<T> * Subscribers::Just(std::string && tag)
{
    return new subscribers::Just<T>(tag);
}

} }

#endif // __NOVEMBERIZING_RX__SUBSCRIBERS__INLINE__HH__
