#include "concurrent.list.hh"

namespace novemberizing { namespace ds {

template <class T, class Concurrent>
inline ConcurrentList<T, Concurrent>::ConcurrentList(void)
{
    FUNCTION_START("");

    Concurrent::on();

    FUNCTION_END("");
}

template <class T, class Concurrent>
inline ConcurrentList<T, Concurrent>::~ConcurrentList(void)
{
    FUNCTION_START("");

    clear();

    FUNCTION_END("");
}

template <class T, class Concurrent>
inline typename ConcurrentList<T, Concurrent>::iterator ConcurrentList<T, Concurrent>::begin(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __list.begin();
}

template <class T, class Concurrent>
inline typename ConcurrentList<T, Concurrent>::iterator ConcurrentList<T, Concurrent>::end(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __list.end();
}

template <class T, class Concurrent>
inline typename ConcurrentList<T, Concurrent>::iterator ConcurrentList<T, Concurrent>::erase(typename ConcurrentList<T, Concurrent>::iterator it)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __list.erase(it);
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::front(const T & v)
{
    FUNCTION_START("");
    __list.push_front(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::front(T && v)
{
    FUNCTION_START("");
    __list.push_front(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::back(const T & v)
{
    FUNCTION_START("");
    __list.push_back(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::back(T && v)
{
    FUNCTION_START("");
    __list.push_back(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::push(const T & v)
{
    FUNCTION_START("");
    __list.push_back(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::push(T && v)
{
    FUNCTION_START("");
    __list.push_back(v);
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::front(std::function<void(T&)> on)
{
    FUNCTION_START("");
    if(on!=nullptr)
    {
        T ret = __list.front();
        __list.pop_front();
        on(ret);
    }
    else
    {
        __list.pop_front();
    }
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::back(std::function<void(T&)> on)
{
    FUNCTION_START("");
    if(on!=nullptr)
    {
        T ret = __list.back();
        __list.pop_back();
        on(ret);
    }
    else
    {
        __list.pop_back();
    }
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::pop(std::function<void(T&)> on)
{
    FUNCTION_START("");
    if(on!=nullptr)
    {
        T ret = __list.front();
        __list.pop_front();
        on(ret);
    }
    else
    {
        __list.pop_front();
    }
    FUNCTION_END("");
}

template <class T, class Concurrent>
inline bool ConcurrentList<T, Concurrent>::empty(void) const { return __list.empty(); }

template <class T, class Concurrent>
inline type::size ConcurrentList<T, Concurrent>::size(void) const { return __list.size(); }

template <class T, class Concurrent>
inline void ConcurrentList<T, Concurrent>::clear(void) { __list.clear(); }

} }
