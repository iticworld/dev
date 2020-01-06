/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__CAPACITY__HH__
#define   __NOVEMBERIZING__CAPACITY__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class capacity
    {
    public:     static uint64 get(uint64 n, uint64 page);
    public:     capacity & operator=(const capacity & o);
    public:     capacity & operator=(capacity && o) noexcept;
    public:     capacity();
    public:     capacity(const capacity & o);
    public:     capacity(capacity && o) noexcept;
    public:     virtual ~capacity();
    };
}

#include <novemberizing/capacity.hp>

#endif // __NOVEMBERIZING__CAPACITY__HH__
