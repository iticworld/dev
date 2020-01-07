/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__INPUT__HH__
#define   __NOVEMBERIZING__INPUT__HH__

namespace novemberizing
{
    class input
    {
    public:     input & operator=(const input & o);
    public:     input & operator=(input && o) noexcept;
    public:     input();
    public:     input(const input & o);
    public:     input(input && o) noexcept;
    public:     virtual ~input();
    };
}

#include <novemberizing/input.hp>

#endif // __NOVEMBERIZING__INPUT__HH__
