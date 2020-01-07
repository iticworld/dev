#ifndef   __NOVEMBERIZING_DS__CONCURRENT__LIST__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT__LIST__HH__

#include <list>
#include <functional>

#include <novemberizing/concurrency/condition.hh>

#include <novemberizing/ds.hh>
#include <novemberizing/ds/on.hh>

namespace novemberizing { namespace ds {

template <class T, class Concurrent = concurrency::Condition>
class ConcurrentList : public Concurrent
{
public:     typedef typename std::list<T>::iterator iterator;
private:    std::list<T> __list;
public:     inline iterator begin(void);
public:     inline iterator end(void);
public:     inline iterator erase(iterator it);
public:     inline void front(const T & v);
public:     inline void front(T && v);
public:     inline void back(const T & v);
public:     inline void back(T && v);
public:     inline void push(const T & v);
public:     inline void push(T && v);
public:     inline void front(std::function<void(T&)> f = nullptr);
public:     inline void back(std::function<void(T&)> f = nullptr);
public:     inline void pop(std::function<void(T&)> f = nullptr);
public:     inline bool empty(void) const;
public:     inline type::size size(void) const;
public:     inline void clear(void);
public:     inline ConcurrentList(void);
public:     inline virtual ~ConcurrentList(void);
};

} }

#include <novemberizing/ds/concurrent.list.inline.hh>

#endif // __NOVEMBERIZING_DS__CONCURRENT__LIST__HH__
