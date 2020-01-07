/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__BINARY_SEARCH_TREE__HH__
#define   __NOVEMBERIZING__BINARY_SEARCH_TREE__HH__

#include <novemberizing/tree.hh>

namespace novemberizing
{
    namespace binary
    {
        namespace search
        {
            template <typename T, typename TUPLE = tuple::single<T> >
            class tree : public novemberizing::tree<T, TUPLE>
            {
            protected:  class node
                        {
                        public:     TUPLE tuple;
                        private:    node * __parent;
                        private:    node * __left;
                        private:    node * __right;
                        public:     node * parent();
                        public:     const node * parent() const;
                        public:     void parent(node * n);
                        public:     node * left();
                        public:     const node * left() const;
                        public:     void left(node * n);
                        public:     node * right();
                        public:     const node * right() const;
                        public:     void right(node * n);
                        public:     void clear();
                        public:     node & operator=(const node & o);
                        public:     node & operator=(node && o) noexcept;
                        public:     node(const TUPLE & v);
                        public:     node(TUPLE && v);
                        public:     node(const TUPLE & v, node * parent);
                        public:     node(TUPLE && v, node * parent);
                        public:     node();
                        public:     node(const node & o);
                        public:     node(node && o) noexcept;
                        public:     virtual ~node();
                        };
            protected:  node * __root;
            protected:  uint64 __size;
            protected:  static const TUPLE & __tuple(node * n);
            protected:  static node * __parent(node * n);
            protected:  static void __parent(node * n, node * x);
            protected:  static node * __sibling(node * n);
            protected:  static node * __minimum(node * n);
            protected:  static node * __maximum(node * n);
            protected:  static uint64 __depth(node * n);
            protected:  static node * __left(node * n);
            protected:  static void __left(node * n, node * x);
            protected:  static node * __right(node * n);
            protected:  static void __right(node * n, node * x);
            protected:  void __change(node * n, node * x);
            protected:  node * __next(node * n) const;
            protected:  node * __previous(node * n) const;
            protected:  node * __add(const TUPLE & o);
            protected:  node * __add(TUPLE && o);
            protected:  node * __del(const T & o);
            protected:  void __copy(const tree<T, TUPLE> & o);
            protected:  node * __search(const T & o) const;
            protected:  node * __search(T && o) const;
            protected:  void __clear();
            protected:  void __clear(function<void (TUPLE &)> f);
            protected:  virtual uint64 previous(uint64 i);
            protected:  virtual uint64 next(uint64 i);
            protected:  virtual TUPLE & reference(uint64 i);
            protected:  virtual TUPLE * pointer(uint64 i);
            public:     virtual bool exist(const TUPLE & o) const;
            public:     virtual void exist(const TUPLE & o, function<void (bool)> f) const;
            public:     virtual bool exist(TUPLE && o) const;
            public:     virtual void exist(TUPLE && o, function<void (bool)> f) const;
            public:     virtual bool add(const TUPLE & o);
            public:     virtual bool add(TUPLE && o);
            public:     virtual void add(const TUPLE & o, function<void (bool)> f);
            public:     virtual void add(TUPLE && o, function<void (bool)> f);
            public:     virtual bool del(const TUPLE & o);
            public:     virtual bool del(TUPLE && o);
            public:     virtual void del(const TUPLE & o, function<void (bool)> f);
            public:     virtual void del(TUPLE && o, function<void (bool)> f);
            public:     virtual void del(const TUPLE & o, function<void (TUPLE &)> f, function<void (const exception &)> e);
            public:     virtual void del(TUPLE && o, function<void (TUPLE &)> f, function<void (const exception &)> e);
            public:     virtual void each(function<void (const TUPLE &)> f) const;
            public:     virtual uint64 size() const;
            public:     virtual void size(function<void (int64)> f) const;
            public:     virtual bool empty() const;
            public:     virtual void empty(function<void (bool)> f) const;
            public:     virtual void clear();
            public:     virtual void clear(function<void (TUPLE &)> f);
            public:     virtual iterator<TUPLE> begin();
            public:     virtual iterator<TUPLE> end();
            public:     virtual const iterator<TUPLE> begin() const;
            public:     virtual const iterator<TUPLE> end() const;
            public:     virtual iterator<TUPLE> get(const T & k);
            public:     virtual const iterator<TUPLE> get(const T & k) const;
            public:     virtual bool del(const T & o);
            public:     virtual bool del(T && o);
            public:     virtual void del(const T & o, function<void (bool)> f);
            public:     virtual void del(T && o, function<void (bool)> f);
            public:     virtual void del(const T & o, function<void (TUPLE &)> f, function<void (const exception &)> e);
            public:     virtual void del(T && o, function<void (TUPLE &)> f, function<void (const exception &)> e);
//            public:     virtual string json(function<string (const TUPLE &)> f);
            public:     tree<T, TUPLE> & operator=(const tree<T, TUPLE> & o);
            public:     tree<T, TUPLE> & operator=(tree<T, TUPLE> && o) noexcept;
            public:     tree();
            public:     tree(const tree<T, TUPLE> & o);
            public:     tree(tree<T, TUPLE> && o) noexcept;
            public:     ~tree() override;
            };
        }
    }
}

#include <novemberizing/binary/search/tree.hp>
#include <novemberizing/binary/search/tree/node.hp>

#endif // __NOVEMBERIZING__BINARY_SEARCH_TREE__HH__
