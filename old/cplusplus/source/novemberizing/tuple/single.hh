/**
 *
 * @author      novemberizing <developer@novemberizing.net>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__SINGLE__HH__
#define   __NOVEMBERIZING__SINGLE__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    namespace tuple
    {
        template <typename A>
        class single
        {
        public:     A first;
        public:     single<A> & operator=(const single<A> & o);
        public:     single<A> & operator=(single<A> && o) noexcept;
        public:     bool operator==(const single<A> & o) const;
        public:     bool operator==(single<A> && o) const;
        public:     bool operator!=(const single<A> & o) const;
        public:     bool operator!=(single<A> && o) const;
        public:     single(const A & first);
        public:     single(A && first);
        public:     single();
        public:     single(const single<A> & o);
        public:     single(single<A> && o) noexcept;
        public:     virtual ~single();
        };
    }
}

#include <novemberizing/tuple/single.hp>

#endif // __NOVEMBERIZING__SINGLE__HH__
