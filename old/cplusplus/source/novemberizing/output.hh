/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__OUTPUT__HH__
#define   __NOVEMBERIZING__OUTPUT__HH__

namespace novemberizing
{
    class output
    {
    public:     output & operator=(const output & o);
    public:     output & operator=(output && o) noexcept;
    public:     output();
    public:     output(const output & o);
    public:     output(output && o) noexcept;
    public:     virtual ~output();
    };
}

#include <novemberizing/output.hp>

#endif // __NOVEMBERIZING__OUTPUT__HH__
