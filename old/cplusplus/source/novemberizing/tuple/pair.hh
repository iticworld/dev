/**
 *
 * @author      novemberizing <developer@novemberizing.net>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__TUPLE_PAIR__HH__
#define   __NOVEMBERIZING__TUPLE_PAIR__HH__

#include <novemberizing/tuple/single.hh>

namespace novemberizing
{
    namespace tuple
    {
        template <typename A, typename B>
        class pair : public single<A>
        {
        public:     B second;
        public:     pair<A, B> & operator=(const pair<A, B> & o);
        public:     pair<A, B> & operator=(pair<A, B> && o) noexcept;
        public:     pair(const A & a, const B & b);
        public:     pair(const A & a, B && b);
        public:     pair(A && a, const B & b);
        public:     pair(A && a, B && b);
        public:     pair();
        public:     pair(const pair<A, B> & o);
        public:     pair(pair<A, B> && o) noexcept;
        public:     ~pair() override;
        };
    }
}

#include <novemberizing/tuple/pair.hp>

#endif // __NOVEMBERIZING__TUPLE_PAIR__HH__
