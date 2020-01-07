/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#ifndef   __NOVEMBERIZING__LINKED_LIST__HH__
#define   __NOVEMBERIZING__LINKED_LIST__HH__

#include <novemberizing/list.hh>

namespace novemberizing
{
    namespace linked
    {
        template <typename T>
        class list : public novemberizing::list<T>
        {
        protected:  class node
                    {
                    protected:  T __value;
                    protected:  node * __previous;
                    protected:  node * __next;
                    public:     T & v()
                                {
                                    return __value;
                                }
                    public:     const T & v() const
                                {
                                    return __value;
                                }
                    public:     node * previous()
                                {
                                    return __previous;
                                }
                    public:     const node * previous() const
                                {
                                    return __previous;
                                }
                    public:     void previous(node * n)
                                {
                                    __previous = n;
                                }
                    public:     node * next()
                                {
                                    return __next;
                                }
                    public:     const node * next() const
                                {
                                    return __next;
                                }
                    public:     void next(node * n)
                                {
                                    __next = n;
                                }
                    public:     node(const T & v, node * previous, node * next) : __value(v), __previous(previous), __next(next)
                                {
                                    if(__previous)
                                    {
                                        __previous->next(this);
                                    }
                                    if(__next)
                                    {
                                        __next->previous(this);
                                    }
                                }
                    public:     node(T && v, node * previous, node * next) : __value(move(v)), __previous(previous), __next(next)
                                {
                                    if(__previous)
                                    {
                                        __previous->next(this);
                                    }
                                    if(__next)
                                    {
                                        __next->previous(this);
                                    }
                                }
                    public:     node & operator=(const node & o)
                                {
                                    if(&o != this)
                                    {
                                        __value = o.__value;
                                        __previous = o.__previous;
                                        __next = o.__next;
                                    }
                                    return *this;
                                }
                    public:     node & operator=(node && o) noexcept
                                {
                                    if(&o != this)
                                    {
                                        __value = move(o.__value);
                                        __previous = o.__previous;
                                        __next = o.__next;

                                        o.__previous = nullptr;
                                        o.__next = nullptr;
                                    }
                                    return *this;
                                }
                    public:     node() : __value(), __previous(nullptr), __next(nullptr)
                                {
                                }
                    public:     node(const node & n) : __value(n.__value), __previous(n.__previous), __next(n.__next)
                                {
                                }
                    public:     node(node && n) noexcept : __value(move(n.__value)), __previous(n.__previous), __next(n.__next)
                                {
                                    n.__previous = nullptr;
                                    n.__next = nullptr;
                                }
                    public:     virtual ~node()
                                {
                                    __previous = nullptr;
                                    __next = nullptr;
                                }
                    };
        protected:  type::size __size;
        protected:  node * __head;
        protected:  node * __tail;
        protected:  virtual void __copy(const list<T> & x)
                    {
                        x.each([this](const T & v){ __add(v); });
                    }
        protected:  virtual void __clear()
                    {
                        node * n = __head;
                        while(n != nullptr)
                        {
                            node * next = n->next();
                            delete n;
                            n = next;
                        }
                        __head = nullptr;
                        __tail = nullptr;
                        __size = 0;
                    }
        protected:  virtual void __clear(callback::single<T &&> f)
                    {
                        if(f != nullptr)
                        {
                            node * n = __head;
                            while(n != nullptr)
                            {
                                node * next = n->next();
                                f(move(n->v()));
                                delete n;
                                n = next;
                            }
                            __head = nullptr;
                            __tail = nullptr;
                            __size = 0;
                        }
                        else
                        {
                            __clear();
                        }
                    }
        protected:  virtual void __each(callback::single<const T &> f) const
                    {
                        if(f != nullptr)
                        {
                            node * n = __head;
                            while(n != nullptr)
                            {
                                f(n->v());
                                n = n->next();
                            }
                        }
                    }
        protected:  virtual bool __exist(const T & v) const
                    {
                        node * n = __head;
                        while(n != nullptr)
                        {
                            if(v == n->v())
                            {
                                return true;
                            }
                            n = n->next();
                        }
                        return false;
                    }
        protected:  virtual void __exist(const T & v, const callback::pair<const T &, bool> & f) const
                    {
                        if(f != nullptr)
                        {
                            node * n = __head;
                            while(n != nullptr)
                            {
                                if(v == n->v())
                                {
                                    f(v, true);
                                    return;
                                }
                                n = n->next();
                            }
                            f(v, false);
                        }
                    }
        protected:  virtual node * __add(T && v)
                    {
                        if(__size != type::size(-1))
                        {
                            node * n = new node(move(v), __tail, __tail != nullptr ? __tail->next() : nullptr);   // NOLINT
                            __tail = n;
                            if(__head == nullptr)
                            {
                                __head = n;
                            }
                            __size += 1;
                            return n;
                        }
                        return nullptr;
                    }
        protected:  virtual node * __add(const T & v)
                    {
                        if(__size != type::size(-1))
                        {
                            node * n = new node(v, __tail, __tail != nullptr ? __tail->next() : nullptr);   // NOLINT
                            __tail = n;
                            if(__head == nullptr)
                            {
                                __head = n;
                            }
                            __size += 1;
                            return n;
                        }
                        return nullptr;
                    }
        protected:  virtual void __del(node * n)
                    {
                        node * previous = n->previous();
                        node * next = n->next();
                        if(previous)
                        {
                            previous->next(next);
                        }
                        if(next)
                        {
                            next->previous(previous);
                        }
                        if(n == __head)
                        {
                            __head = next;
                        }
                        if(n == __tail)
                        {
                            __tail = previous;
                        }
                        __size -= 1;
                        delete n;
                    }
        protected:  virtual bool __del(const T & v)
                    {
                        node * n = __head;
                        while(n != nullptr)
                        {
                            if(v == n->v())
                            {
                                __del(n);
                                return true;
                            }
                            n = n->next();
                        }
                        return false;
                    }
        protected:  virtual void __del(const T & v, const callback::pair<T &&, bool> & f)
                    {
                        if(f != nullptr)
                        {
                            node * n = __head;
                            while(n != nullptr)
                            {
                                if(v == n->v())
                                {
                                    f(move(n->v()), true);
                                    __del(n);
                                    return;
                                }
                                n = n->next();
                            }
                            f(move(const_cast<T&>(v)), false);
                        }
                        else
                        {
                            __del(v);
                        }
                    }
        public:     type::size size() const override
                    {
                        return __size;
                    }
        public:     void size(callback::single<type::size> f) const override
                    {
                        if(f != nullptr)
                        {
                            f(__size);
                        }
                    }
        public:     bool add(const T & v) override
                    {
                        return __add(v)!=nullptr;
                    }
        public:     void add(const T & v, callback::pair<const T &, bool> f) override
                    {
                        if(f != nullptr)
                        {
                            node * n = __add(v);
                            f(n->v(), true);
                        }
                        else
                        {
                            __add(v);
                        }
                    }
        public:     virtual bool add(T && v)
                    {
                        return __add(move(v)) != nullptr;
                    }
        public:     virtual void add(T && v, callback::pair<const T &, bool> f)
                    {
                        if(f != nullptr)
                        {
                            node * n = __add(move(v));
                            f(n->v(), true);
                        }
                        else
                        {
                            __add(move(v));
                        }
                    }
        public:     bool del(const T & v) override
                    {
                        return __del(v);
                    }
        public:     void del(const T & v, callback::pair<T &&, bool> f) override
                    {
                        __del(v, f);
                    }
        public:     bool empty() const override
                    {
                        return __size == 0;
                    }
        public:     void empty(callback::single<bool> f) const override
                    {
                        if(f != nullptr)
                        {
                            f(__size == 0);
                        }
                    }
        public:     bool exist(const T & v) const override
                    {
                        return __exist(v);
                    }
        public:     void exist(const T & v, callback::pair<const T &, bool> f) const override
                    {
                        return __exist(v, f);
                    }
        public:     void clear() override
                    {
                        __clear();
                    }
        public:     void clear(callback::single<T &&> f) override
                    {
                        __clear(f);
                    }
        public:     void each(callback::single<const T &> f) const override
                    {
                        __each(f);
                    }
        public:     list<T> & operator=(const list<T> & o)
                    {
                        if(&o != this)
                        {
                            __clear();
                            __copy(o);
                        }
                        return *this;
                    }
        public:     list<T> & operator=(list<T> && o) noexcept
                    {
                        if(&o != this)
                        {
                            __clear();
                            __size = o.__size;
                            __head = o.__head;
                            __tail = o.__tail;

                            o.__size = 0;
                            o.__head = nullptr;
                            o.__tail = nullptr;
                        }
                        return *this;
                    }
        public:     list() : __size(0), __head(nullptr), __tail(nullptr)
                    {
                        FUNCTION_LOG("");
                    }
        public:     list(const list<T> & o) : __size(0), __head(nullptr), __tail(nullptr)
                    {
                        __copy(o);
                    }
        public:     list(list<T> && o) noexcept : __size(o.__size), __head(o.__head), __tail(o.__tail)
                    {
                        o.__size = 0;
                        o.__head = nullptr;
                        o.__tail = nullptr;
                    }
        public:     ~list() override
                    {
                        __clear();
                    }
        };
    }
}

#endif // __NOVEMBERIZING__LINKED_LIST__HH__
