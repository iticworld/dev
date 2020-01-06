#ifndef   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_ITERATOR__INLINE__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_ITERATOR__INLINE__HH__

namespace novemberizing { namespace ds {

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::iterator::iterator(void) : __node(nullptr)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::iterator::iterator(Node * node) : __node(node)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::iterator::iterator(const iterator & it) : __node(it.__node)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::iterator::~iterator(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

// template <class T, class Concurrent>
// typename ConcurrentLinkedSet<T, Concurrent>::Node * ConcurrentLinkedSet<T, Concurrent>::iterator::node(void) const
// {
//     return __node;
// }

template <class T, class Concurrent>
inline T & ConcurrentLinkedSet<T, Concurrent>::iterator::operator*(void)
{
    FUNCTION_START("");
    if(__node==nullptr){ throw Throwable("__node==nullptr"); }
    FUNCTION_END("");
    return __node->__value;
}

template <class T, class Concurrent>
inline const T & ConcurrentLinkedSet<T, Concurrent>::iterator::operator*(void) const
{
    FUNCTION_START("");
    if(__node==nullptr){ throw Throwable("__node==nullptr"); }
    FUNCTION_END("");
    return __node->__value;
}

template <class T, class Concurrent>
inline T * ConcurrentLinkedSet<T, Concurrent>::iterator::operator->(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __node!=nullptr ? &(__node->__value) : nullptr;
}

template <class T, class Concurrent>
inline const T * ConcurrentLinkedSet<T, Concurrent>::iterator::operator->(void) const
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __node!=nullptr ? &(__node->__value) : nullptr;
}

template <class T, class Concurrent>
inline bool ConcurrentLinkedSet<T, Concurrent>::iterator::operator==(const iterator & it) const
{
    return it.__node==__node;
}

template <class T, class Concurrent>
inline bool ConcurrentLinkedSet<T, Concurrent>::iterator::operator!=(const iterator & it) const
{
    return it.__node!=__node;
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator & ConcurrentLinkedSet<T, Concurrent>::iterator::operator++(void)
{
    FUNCTION_START("");
    __node = __node->__next;
    FUNCTION_END("");
    return *this;
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator ConcurrentLinkedSet<T, Concurrent>::iterator::operator++(int)
{
    FUNCTION_START("");
    ConcurrentLinkedSet<T, Concurrent>::Node * current =  __node;
    __node = __node->__next;
    FUNCTION_END("");
    return iterator(current);
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator & ConcurrentLinkedSet<T, Concurrent>::iterator::operator=(const iterator & it)
{
    FUNCTION_START("");
    __node = it.__node;
    FUNCTION_END("");
    return *this;
}

} }

#endif // __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_ITERATOR__INLINE__HH__
