#ifndef   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_NODE__INLINE__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_NODE__INLINE__HH__

namespace novemberizing { namespace ds {

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::Node::Node(ConcurrentLinkedSet<T, Concurrent> * container, const T & v) : __container(container), __value(v)
{
    FUNCTION_START("");

    if(__container->__front==nullptr && __container->__back==nullptr)
    {
        __container->__front = __container->__back = this;
        __previous = nullptr;
        __next = nullptr;
    }
    else
    {
        __previous = __container->__back;
        __previous->__next = this;
        __next = nullptr;
    }
    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::Node::~Node(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET_NODE__INLINE__HH__
