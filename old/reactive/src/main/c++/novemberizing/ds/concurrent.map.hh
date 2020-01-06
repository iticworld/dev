#ifndef   __NOVEMBERIZING_DS__CONCURRENT_MAP__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_MAP__HH__

#include <map>
#include <functional>

#include <novemberizing/ds.hh>
#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace ds {

template <class K, class V, class Concurrent = concurrency::Sync>
class ConcurrentMap : public Concurrent
{
public:     typedef typename std::map<K,V>::iterator iterator;
private:    std::map<K, V> __map;
public:     inline iterator begin(void);
public:     inline iterator end(void);
public:     inline iterator erase(iterator it);
public:     inline void put(const K & key, const V & value, std::function<void(V&)> f = nullptr);
public:     inline void put(K && key, const V & value, std::function<void(V&)> f = nullptr);
public:     inline void put(const K & key, V && value, std::function<void(V&)> f = nullptr);
public:     inline void put(K && key, V && value, std::function<void(V&)> f = nullptr);
public:     inline void get(const K & key, std::function<void(V&)> f = nullptr);
public:     inline void get(K && key, std::function<void(V&)> f = nullptr);
public:     inline void del(const K & key, std::function<void(V&)> f = nullptr);
public:     inline void del(K && key, std::function<void(V&)> f = nullptr);
public:     inline bool exist(const K & key) const;
public:     inline bool exist(K && key) const;
public:     inline bool empty(void) const;
public:     inline type::size size(void) const;
public:     inline void clear(void);
public:     ConcurrentMap(void);
public:     virtual ~ConcurrentMap(void);
};

} }

#include <novemberizing/ds/concurrent.map.inline.hh>

#endif // __NOVEMBERIZING_DS__CONCURRENT_MAP__HH__
