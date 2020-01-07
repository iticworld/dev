/**
 *
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 7.
 */

#ifndef   __NOVEMBERIZING__TRIPLE__HH__
#define   __NOVEMBERIZING__TRIPLE__HH__

#include <novemberizing/tuple/pair.hh>

namespace novemberizing
{
    namespace tuple
    {
        template <typename A, typename B, typename C>
        class triple : public pair<A, B>
        {
        public:     C third;
        public:     triple<A, B, C> & operator=(const triple<A, B, C> & o);
        public:     triple<A, B, C> & operator=(triple<A, B, C> && o) noexcept;
        public:     triple();
        public:     triple(const triple<A, B, C> & o);
        public:     triple(triple<A, B, C> && o) noexcept;
        public:     ~triple() override;
        };
    }
}

#include <novemberizing/tuple/triple.hh>

#endif // __NOVEMBERIZING__TRIPLE__HH__
