#ifndef   __NOVEMBERIZING_DS__CONCURRENT_MAP__INLINE__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_MAP__INLINE__HH__

namespace novemberizing { namespace ds {

template <class K, class V, class Concurrent>
ConcurrentMap<K, V, Concurrent>::ConcurrentMap(void)
{
    FUNCTION_START("");

    Concurrent::on();

    FUNCTION_END("");
}

template <class K, class V, class Concurrent>
ConcurrentMap<K, V, Concurrent>::~ConcurrentMap(void)
{
    FUNCTION_START("");

    clear();

    FUNCTION_END("");
}

template <class K, class V, class Concurrent>
typename ConcurrentMap<K, V, Concurrent>::iterator ConcurrentMap<K, V, Concurrent>::begin(void)
{
    return __map.begin();
}

template <class K, class V, class Concurrent>
typename ConcurrentMap<K, V, Concurrent>::iterator ConcurrentMap<K, V, Concurrent>::end(void)
{
    return __map.end();
}

template <class K, class V, class Concurrent>
typename ConcurrentMap<K, V, Concurrent>::iterator ConcurrentMap<K, V, Concurrent>::erase(typename ConcurrentMap<K, V, Concurrent>::iterator it)
{
    __map.erase(it++);
    return it;
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::put(const K & key, const V & value, std::function<void(V&)> f)
{
    std::pair<typename std::map<K, V>::iterator, bool> inserted = __map.insert(std::pair<K,V>(key, value));
    if(!inserted.second)
    {
        if(f!=nullptr)
        {
            f(inserted.first->second);
        }
        inserted.first->second = value;
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::put(K && key, const V & value, std::function<void(V&)> f)
{
    std::pair<typename std::map<K, V>::iterator, bool> inserted = __map.insert(std::pair<K,V>(key, value));
    if(!inserted.second)
    {
        if(f!=nullptr)
        {
            f(inserted.first->second);
        }
        inserted.first->second = value;
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::put(const K & key, V && value, std::function<void(V&)> f)
{
    std::pair<typename std::map<K, V>::iterator, bool> inserted = __map.insert(std::pair<K,V>(key, value));
    if(!inserted.second)
    {
        if(f!=nullptr)
        {
            f(inserted.first->second);
        }
        inserted.first->second = value;
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::put(K && key, V && value, std::function<void(V&)> f)
{
    std::pair<typename std::map<K, V>::iterator, bool> inserted = __map.insert(std::pair<K,V>(key, value));
    if(!inserted.second)
    {
        if(f!=nullptr)
        {
            f(inserted.first->second);
        }
        inserted.first->second = value;
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::get(const K & key, std::function<void(V&)> f)
{
    typename std::map<K, V>::iterator it = __map.find(key);
    if(it!=__map.end())
    {
        if(f!=nullptr)
        {
            f(it.first->second);
        }
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::get(K && key, std::function<void(V&)> f)
{
    typename std::map<K, V>::iterator it = __map.find(key);
    if(it!=__map.end())
    {
        __map.erase(it);
        if(f!=nullptr)
        {
            f(it.first->second);
        }
    }
}



template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::del(const K & key, std::function<void(V&)> f)
{
    typename std::map<K, V>::iterator it = __map.find(key);
    if(it!=__map.end())
    {
        __map.erase(it);
        if(f!=nullptr)
        {
            f(it.first->second);
        }
    }
}

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::del(K && key, std::function<void(V&)> f)
{
    typename std::map<K, V>::iterator it = __map.find(key);
    __map.erase(it);
    return it!=__map.end() ? it->second : V();
}

template <class K, class V, class Concurrent>
bool ConcurrentMap<K, V, Concurrent>::exist(const K & key) const
{
    typename std::map<K, V>::iterator it = __map.find(key);
    return it!=__map.end();
}

template <class K, class V, class Concurrent>
bool ConcurrentMap<K, V, Concurrent>::exist(K && key) const
{
    typename std::map<K, V>::iterator it = __map.find(key);
    return it!=__map.end();
}

template <class K, class V, class Concurrent>
bool ConcurrentMap<K, V, Concurrent>::empty(void) const { return __map.empty(); }

template <class K, class V, class Concurrent>
type::size ConcurrentMap<K, V, Concurrent>::size(void) const { return __map.size(); }

template <class K, class V, class Concurrent>
void ConcurrentMap<K, V, Concurrent>::clear(void) { return __map.clear(); }

} }

#endif // __NOVEMBERIZING_DS__CONCURRENT_MAP__INLINE__HH__
