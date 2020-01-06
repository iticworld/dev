#ifndef   __NOVEMBERIZING_DS__CONCURRENT__SET__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT__SET__HH__

#include <set>
#include <map>

#include <novemberizing/ds.hh>

#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace ds {

template <class T, class Concurrent = concurrency::Sync>
class ConcurrentSet : public Concurrent
{
public:     typedef typename std::set<T>::iterator iterator;
private:    std::set<T> __set;
public:     inline iterator begin(void);
public:     inline iterator end(void);
public:     inline iterator erase(iterator it);
public:     inline bool add(const T & v);
public:     inline bool add(const T && v);
public:     inline bool del(const T & v);
public:     inline bool del(const T && v);
public:     inline bool exist(const T & v);
public:     inline bool exist(const T && v);
public:     inline bool empty(void) const;
public:     inline type::size size(void) const;
public:     inline void clear(void);
public:     inline ConcurrentSet(void);
public:     inline virtual ~ConcurrentSet(void);
};

} }

#include <novemberizing/ds/concurrent.set.inline.hh>

#endif // __NOVEMBERIZING_DS__CONCURRENT__SET__HH__
