#ifndef   __NOVEMBERIZING_DS__CONCURRENT_SET__INLINE__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_SET__INLINE__HH__

#include <novemberizing/ds/concurrent.set.hh>

namespace novemberizing { namespace ds {

template <class T, class Concurrent>
ConcurrentSet<T, Concurrent>::ConcurrentSet(void)
{
    FUNCTION_START("");

    Concurrent::on();

    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentSet<T, Concurrent>::~ConcurrentSet(void)
{
    FUNCTION_START("");

    clear();

    FUNCTION_END("");
}

template <class T, class Concurrent>
inline typename ConcurrentSet<T, Concurrent>::iterator ConcurrentSet<T, Concurrent>::begin(void)
{
    return __set.begin();
}

template <class T, class Concurrent>
inline typename ConcurrentSet<T, Concurrent>::iterator ConcurrentSet<T, Concurrent>::end(void)
{
    return __set.end();
}

template <class T, class Concurrent>
inline typename ConcurrentSet<T, Concurrent>::iterator ConcurrentSet<T, Concurrent>::erase(typename ConcurrentSet<T, Concurrent>::iterator it)
{
    __set.erase(it++);
    return it;
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::add(const T & v)
{
    std::pair<typename std::set<T>::iterator, bool> inserted = __set.insert(v);
    return inserted.second;
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::add(const T && v)
{
    std::pair<typename std::set<T>::iterator, bool> inserted = __set.insert(v);
    return inserted.second;
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::del(const T & v)
{
    type::size i = __set.erase(v);
    return i==1;
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::del(const T && v)
{
    type::size i = __set.erase(v);
    return i==1;
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::exist(const T & v)
{
    return __set.find(v)!=__set.end();
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::exist(const T && v)
{
    return __set.find(v)!=__set.end();
}

template <class T, class Concurrent>
inline bool ConcurrentSet<T, Concurrent>::empty(void) const { return __set.empty(); }

template <class T, class Concurrent>
inline type::size ConcurrentSet<T, Concurrent>::size(void) const { return __set.size(); }

template <class T, class Concurrent>
inline void ConcurrentSet<T, Concurrent>::clear(void) { return __set.clear(); }

} }

#endif // __NOVEMBERIZING_DS__CONCURRENT_SET__INLINE__HH__
