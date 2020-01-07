#ifndef   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__HH__

#include <map>

#include <novemberizing/concurrency/sync.hh>
#include <novemberizing/ds.hh>
#include <novemberizing/ds/throwable.hh>

namespace novemberizing { namespace ds {

using namespace ds;

template <class T, class Concurrent = concurrency::Sync>
class ConcurrentLinkedSet : public Concurrent
{
private:    class Node
            {
            private:    ConcurrentLinkedSet<T, Concurrent> * __container;
            private:    T __value;
            private:    Node * __previous;
            private:    Node * __next;
            public:     Node(ConcurrentLinkedSet<T, Concurrent> * container, const T & v);
            public:     virtual ~Node(void);
            public:     friend class ConcurrentLinkedSet<T, Concurrent>;
            };
public:     class iterator
            {
            private:    Node * __node;
            // private:    Node * node(void) const;
            public:     inline T & operator*(void);
            public:     inline const T & operator*(void) const;
            public:     inline T * operator->(void);
            public:     inline const T * operator->(void) const;
            public:     inline iterator& operator++(void);
            public:     inline iterator operator++(int);
            public:     inline iterator & operator=(const iterator & it);
            public:     inline bool operator==(const iterator & it) const;
            public:     inline bool operator!=(const iterator & it) const;
            public:     iterator(void);
            private:    iterator(Node * node);
            public:     iterator(const iterator & iterator);
            public:     virtual ~iterator(void);
            public:     friend class ConcurrentLinkedSet<T, Concurrent>;
            };
private:    std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *> __map;
private:    ConcurrentLinkedSet<T, Concurrent>::Node * __front;
private:    ConcurrentLinkedSet<T, Concurrent>::Node * __back;
public:     inline iterator begin(void);
public:     inline iterator end(void);
public:     inline iterator erase(iterator it);
public:     inline bool add(const T & v);
public:     inline bool add(T && v);
public:     inline bool del(const T & v);
public:     inline bool del(T && v);
public:     inline bool exist(const T & v);
public:     inline bool exist(T && v);
public:     inline bool empty(void) const;
public:     inline type::size size(void) const;
public:     inline void clear(void);
public:     ConcurrentLinkedSet(void);
public:     virtual ~ConcurrentLinkedSet(void);
public:     friend class Node;
};

} }

#include <novemberizing/ds/concurrent.linked.set.inline.hh>
#include <novemberizing/ds/concurrent.linked.set.node.inline.hh>
#include <novemberizing/ds/concurrent.linked.set.iterator.inline.hh>

#endif // __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__HH__
