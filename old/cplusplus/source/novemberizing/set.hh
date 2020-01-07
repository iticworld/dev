/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__SET__HH__
#define   __NOVEMBERIZING__SET__HH__

#include <novemberizing.hh>
#include <novemberizing/collection.hh>

namespace novemberizing
{
    template <typename T>
    class set : public collection<T>, public iterator<T>::accessor
    {
    public:     set<T> & operator=(const set<T> & o);
    public:     set<T> & operator=(set<T> && o) noexcept;
    public:     set();
    public:     set(const set<T> & o);
    public:     set(set<T> && o) noexcept;
    public:     ~set() override;
    };
}

#include <novemberizing/set.hp>

#endif // __NOVEMBERIZING__SET__HH__
