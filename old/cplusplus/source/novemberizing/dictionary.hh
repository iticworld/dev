/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__DICTIONARY__HH__
#define   __NOVEMBERIZING__DICTIONARY__HH__

#include <novemberizing/collection.hh>
#include <novemberizing/tuple/single.hh>

namespace novemberizing
{
    template <typename T, typename TUPLE = tuple::single<T> >
    class dictionary : public collection<TUPLE>
    {
    public:     dictionary<T, TUPLE> & operator=(const dictionary<T, TUPLE> & o);
    public:     dictionary<T, TUPLE> & operator=(dictionary<T, TUPLE> && o) noexcept;
    public:     dictionary();
    public:     dictionary(const dictionary<T, TUPLE> & o);
    public:     dictionary(dictionary<T, TUPLE> && o) noexcept;
    public:     ~dictionary() override;
    };
}

#include <novemberizing/dictionary.hp>

#endif // __NOVEMBERIZING__DICTIONARY__HH__
