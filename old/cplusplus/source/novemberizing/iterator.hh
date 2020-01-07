/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 6.
 */

#ifndef   __NOVEMBERIZING__ITERATOR__HH__
#define   __NOVEMBERIZING__ITERATOR__HH__

#include <novemberizing/container.hh>

namespace novemberizing
{
    template <typename T>
    class iterator
    {
    public:     class accessor
                {
                public:     static iterator<T> create(container::base<T> * p, uint64 i);
                public:     static iterator<T> create(const container::base<T> * p, uint64 i);
                public:     accessor & operator=(const accessor & o);
                public:     accessor & operator=(accessor && o) noexcept;
                public:     accessor();
                public:     accessor(const accessor & o);
                public:     accessor(accessor && o) noexcept;
                public:     virtual ~accessor();
                };
    private:    container::base<T> * __container;
    private:    uint64 __index;
    public:     T & operator*();
    public:     const T & operator*() const;
    public:     T * operator->();
    public:     const T * operator->() const;
    public:     iterator<T> & operator++();
    public:     iterator<T> & operator--();
    public:     iterator<T> operator++(int);
    public:     iterator<T> operator--(int);
    public:     iterator<T> & operator=(const iterator<T> & o);
    public:     iterator<T> & operator=(iterator<T> && o) noexcept;
    public:     bool operator==(const iterator<T> & o) const;
    public:     bool operator!=(const iterator<T> & o) const;
    public:     iterator();
    public:     iterator(const iterator<T> & o);
    public:     iterator(iterator<T> && o) noexcept;
    public:     virtual ~iterator();
    };
}

#include <novemberizing/iterator.hp>
#include <novemberizing/iterator/accessor.hp>

#endif // __NOVEMBERIZING__ITERATOR__HH__
