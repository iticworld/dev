/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#ifndef   __NOVEMBERIZING__LIST__HH__
#define   __NOVEMBERIZING__LIST__HH__

#include <novemberizing/collection.hh>

namespace novemberizing
{
    template <typename T>
    class list : public collection<T>
    {
    public:     list<T> & operator=(const list<T> & o);
    public:     list<T> & operator=(list<T> && o) noexcept;
    public:     list();
    public:     list(const list<T> & o);
    public:     list(list<T> && o) noexcept;
    public:     ~list();
    };
}

#include <novemberizing/list.hp>

#endif // __NOVEMBERIZING__LIST__HH__
