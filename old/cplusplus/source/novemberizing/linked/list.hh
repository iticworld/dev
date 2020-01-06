/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 6.
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
                    private:    T __value;
                    private:    node * __previous;
                    private:    node * __next;
                    public:     void previous(node * p);
                    public:     void next(node * p);
                    public:     const node * previous() const;
                    public:     const node * next() const;
                    public:     node * previous();
                    public:     node * next();
                    public:     T & v();
                    public:     const T & v() const;
                    public:     T * p();
                    public:     const T * p() const;
                    public:     node & operator=(const node & o);
                    public:     node & operator=(node && o) noexcept;
                    public:     node(const T & o, node * previous, node * next);
                    public:     node(T && o, node * previous, node * next);
                    public:     node();
                    public:     node(const node & o);
                    public:     node(node && o) noexcept;
                    public:     virtual ~node();
                    };
        public:     node * __head;
        public:     node * __tail;
        public:     uint64 __size;
        protected:  virtual bool __add(const T & o);
        protected:  virtual bool __add(T && o);
        protected:  virtual typename list<T>::node * __find(const T & o) const;
        protected:  virtual typename list<T>::node * __find(T && o) const;
        protected:  virtual bool __del(typename list<T>::node * n);
        protected:  virtual void __clear();
        protected:  virtual void __clear(function<void (T &)> f);
        protected:  virtual uint64 previous(uint64 i);
        protected:  virtual uint64 next(uint64 i);
        protected:  virtual T & reference(uint64 i);
        protected:  virtual T * pointer(uint64 i);
        public:     virtual uint64 size() const;
        public:     virtual void size(function<void (int64)> f) const;
        public:     virtual bool empty() const;
        public:     virtual void empty(function<void (bool)> f) const;
        public:     virtual void clear();
        public:     virtual void clear(function<void (T &)> f);
        public:     virtual bool exist(const T & o) const;
        public:     virtual void exist(const T & o, function<void (bool)> f) const;
        public:     virtual bool exist(T && o) const;
        public:     virtual void exist(T && o, function<void (bool)> f) const;
        public:     virtual bool add(const T & o);
        public:     virtual bool add(T && o);
        public:     virtual void add(const T & o, function<void (bool)> f);
        public:     virtual void add(T && o, function<void (bool)> f);
        public:     virtual bool del(const T & o);
        public:     virtual bool del(T && o);
        public:     virtual void del(const T & o, function<void (bool)> f);
        public:     virtual void del(T && o, function<void (bool)> f);
        public:     virtual void del(const T & o, function<void (T &)> f, function<void (const exception &)> e);
        public:     virtual void del(T && o, function<void (T &)> f, function<void (const exception &)> e);
        public:     virtual void each(function<void (const T &)> f) const;
        public:     virtual iterator<T> begin();
        public:     virtual iterator<T> end();
        public:     virtual const iterator<T> begin() const;
        public:     virtual const iterator<T> end() const;
        public:     list<T> & operator=(const list<T> & o);
        public:     list<T> & operator=(list<T> && o) noexcept;
        public:     list();
        public:     list(const list<T> & o);
        public:     list(list<T> && o) noexcept;
        public:     ~list() override;
        };
    }
}

#include <novemberizing/linked/list.hp>
#include <novemberizing/linked/list/node.hp>

#endif // __NOVEMBERIZING__LINKED_LIST__HH__
