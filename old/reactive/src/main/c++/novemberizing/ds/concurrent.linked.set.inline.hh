#ifndef   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__INLINE__HH__
#define   __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__INLINE__HH__

namespace novemberizing { namespace ds {

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::ConcurrentLinkedSet(void) : __front(nullptr), __back(nullptr)
{
    FUNCTION_START("");

    Concurrent::on();

    FUNCTION_END("");
}

template <class T, class Concurrent>
ConcurrentLinkedSet<T, Concurrent>::~ConcurrentLinkedSet(void)
{
    FUNCTION_START("");

    clear();

    FUNCTION_END("");
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::add(const T & v)
{
    FUNCTION_START("");

    std::pair<typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator, bool> inserted = __map.insert(std::pair<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>(v, nullptr));
    if(inserted.second)
    {
        inserted.first->second = new typename ConcurrentLinkedSet<T, Concurrent>::Node(this, v);
    }
    else
    {
        CAUTION_LOG("fail to __map.insert(...)");
    }

    FUNCTION_END("");
    return inserted.second;
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::add(T && v)
{
    FUNCTION_START("");

    std::pair<typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator, bool> inserted = __map.insert(std::pair<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>(v, nullptr));
    if(inserted.second)
    {
        inserted.first->second = new typename ConcurrentLinkedSet<T, Concurrent>::Node(this, v);
    }
    else
    {
        CAUTION_LOG("fail to __map.insert(...)");
    }

    FUNCTION_END("");
    return inserted.second;
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::exist(const T & v)
{
    FUNCTION_START("");
    typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator found = __map.find(v);
    FUNCTION_END("");
    return found!=__map.end();
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::exist(T && v)
{
    FUNCTION_START("");
    typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator found = __map.find(v);
    FUNCTION_END("");
    return found!=__map.end();
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::empty(void) const
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __map.empty();
}

template <class T, class Concurrent>
type::size ConcurrentLinkedSet<T, Concurrent>::size(void) const
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __map.size();
}

template <class T, class Concurrent>
void ConcurrentLinkedSet<T, Concurrent>::clear(void)
{
    FUNCTION_START("");
    __map.clear();
    ConcurrentLinkedSet<T, Concurrent>::Node * node = __front;
    while(node!=nullptr)
    {
        if(node->__next!=nullptr)
        {
            node = node->__next;
            delete node->__previous;
        }
        else
        {
            delete node;
            node = nullptr;
        }
    }
    __front = nullptr;
    __back = nullptr;
    FUNCTION_END("");
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::del(const T & v)
{
    FUNCTION_START("");
    typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator found = __map.find(v);
    if(found!=__map.end())
    {
        ConcurrentLinkedSet<T, Concurrent>::Node * node = found->second;
        if(node->__previous==nullptr)
        {
            if(node->__next==nullptr)
            {
                __front = nullptr;
                __back = nullptr;
            }
            else
            {
                node->__next->__previous = nullptr;
                __front = node->__next;
            }
        }
        else
        {
            if(node->__next==nullptr)
            {
                node->__previous->__next = nullptr;
                __back = node->__previous;
            }
            else
            {
                node->__previous->__next = node->__next;
                node->__next->__previous = node->__previous;
            }
        }
        delete node;
    }
    FUNCTION_END("");
    return found!=__map.end();
}

template <class T, class Concurrent>
bool ConcurrentLinkedSet<T, Concurrent>::del(T && v)
{
    FUNCTION_START("");
    typename std::map<T, typename ConcurrentLinkedSet<T, Concurrent>::Node *>::iterator found = __map.find(v);
    if(found!=__map.end())
    {
        ConcurrentLinkedSet<T, Concurrent>::Node * node = found.second;
        if(node->__previous==nullptr)
        {
            if(node->__next==nullptr)
            {
                __front = nullptr;
                __back = nullptr;
            }
            else
            {
                node->__next->__previous = nullptr;
                __front = node->__next;
            }
        }
        else
        {
            if(node->__next==nullptr)
            {
                node->__previous->__next = nullptr;
                __back = node->__previous;
            }
            else
            {
                node->__previous->__next = node->__next;
                node->__next->__previous = node->__previous;
            }
        }
        delete node;
    }
    FUNCTION_END("");
    return found!=__map.end();
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator ConcurrentLinkedSet<T, Concurrent>::begin(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return iterator(__front);
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator ConcurrentLinkedSet<T, Concurrent>::end(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
    return iterator(nullptr);
}

template <class T, class Concurrent>
inline typename ConcurrentLinkedSet<T, Concurrent>::iterator ConcurrentLinkedSet<T, Concurrent>::erase(iterator it)
{
    Node * next = nullptr;
    if(it.__node!=nullptr)
    {
        next = it.__node->__next;
        if(!del(it.__node->__value))
        {
            next = nullptr;
            ERROR_LOG("del(...)==false");
        }
    }
    else
    {
        CAUTION_LOG("it.__node==nullptr");
    }
    return iterator(next);
}

} }

#endif // __NOVEMBERIZING_DS__CONCURRENT_LINKED_SET__INLINE__HH__
