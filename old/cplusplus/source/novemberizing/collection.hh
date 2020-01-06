/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#ifndef   __NOVEMBERIZING__COLLECTION__HH__
#define   __NOVEMBERIZING__COLLECTION__HH__

#include <novemberizing/container.hh>
#include <novemberizing/iterator.hh>

namespace novemberizing
{
    template <typename T>
    class collection : public container, public container::base<T>, public iterator<T>::accessor
    {
    public:     virtual bool exist(const T & o) const = 0;
    public:     virtual void exist(const T & o, function<void (bool)> f) const = 0;
    public:     virtual bool exist(T && o) const = 0;
    public:     virtual void exist(T && o, function<void (bool)> f) const = 0;
    public:     virtual bool add(const T & o) = 0;
    public:     virtual bool add(T && o) = 0;
    public:     virtual void add(const T & o, function<void (bool)> f) = 0;
    public:     virtual void add(T && o, function<void (bool)> f) = 0;
    public:     virtual bool del(const T & o) = 0;
    public:     virtual bool del(T && o) = 0;
    public:     virtual void del(const T & o, function<void (bool)> f) = 0;
    public:     virtual void del(T && o, function<void (bool)> f) = 0;
    public:     virtual void del(const T & o, function<void (T &)> f, function<void (const exception &)> e) = 0;
    public:     virtual void del(T && o, function<void (T &)> f, function<void (const exception &)> e) = 0;
    public:     virtual void each(function<void (const T &)> f) const = 0;
    public:     virtual void clear() = 0;
    public:     virtual void clear(function<void (T &)> f) = 0;
    public:     virtual const iterator<T> begin() const = 0;
    public:     virtual const iterator<T> end() const = 0;
    public:     virtual iterator<T> begin() = 0;
    public:     virtual iterator<T> end() = 0;
    public:     collection<T> & operator=(const collection<T> & o);
    public:     collection<T> & operator=(collection<T> && o) noexcept;
    public:     collection();
    public:     collection(const collection<T> & o);
    public:     collection(collection<T> && o) noexcept;
    public:     ~collection() override;
    };
}

#include <novemberizing/collection.hp>

#endif // __NOVEMBERIZING__COLLECTION__HH__
