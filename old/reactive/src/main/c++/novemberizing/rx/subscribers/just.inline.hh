#ifndef   __NOVEMBERIZING_RX_SUBSCRIBERS__JUST__HH__
#define   __NOVEMBERIZING_RX_SUBSCRIBERS__JUST__HH__

namespace novemberizing { namespace rx { namespace subscribers {

template <class T>
Just<T>::Just(void) : __tag("just")
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Just<T>::Just(const std::string & tag) : __tag(tag)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Just<T>::Just(std::string && tag) : __tag(tag)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Just<T>::~Just(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Just<T>::onNext(const T & item)
{
    std::cout<<__tag<<" "<<item<<std::endl;
}

template <class T>
void Just<T>::onError(const Throwable & exception)
{
    std::cout<<__tag<<" exception: "<<exception<<std::endl;
}

template <class T>
void Just<T>::onComplete(void)
{
    std::cout<<__tag<<" completed"<<std::endl;
}

} } }

#endif // __NOVEMBERIZING_RX_SUBSCRIBERS__JUST__HH__
