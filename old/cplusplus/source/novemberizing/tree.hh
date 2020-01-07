/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__TREE__HH__
#define   __NOVEMBERIZING__TREE__HH__

#include <novemberizing/dictionary.hh>

namespace novemberizing
{
    template <typename T, typename TUPLE = tuple::single<T> >
    class tree : public dictionary<T, TUPLE>
    {
    public:     virtual iterator<TUPLE> get(const T & k) = 0;
    public:     virtual const iterator<TUPLE> get(const T & k) const = 0;
    public:     virtual bool del(const T & o) = 0;
    public:     virtual bool del(T && o) = 0;
    public:     virtual void del(const T & o, function<void (bool)> f) = 0;
    public:     virtual void del(T && o, function<void (bool)> f) = 0;
    public:     virtual void del(const T & o, function<void (TUPLE &)> f, function<void (const exception &)> e) = 0;
    public:     virtual void del(T && o, function<void (TUPLE &)> f, function<void (const exception &)> e) = 0;
    public:     tree<T, TUPLE> & operator=(const tree<T, TUPLE> & o);
    public:     tree<T, TUPLE> & operator=(tree<T, TUPLE> && o) noexcept;
    public:     tree();
    public:     tree(const tree<T, TUPLE> & o);
    public:     tree(tree<T, TUPLE> && o) noexcept;
    public:     ~tree() override;
    };
}

#include <novemberizing/tree.hp>

#endif // __NOVEMBERIZING__TREE__HH__
