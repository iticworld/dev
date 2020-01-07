/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__EXCEPTION__HH__
#define   __NOVEMBERIZING__EXCEPTION__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class exception
    {
    public:     exception & operator=(const exception & o);
    public:     exception & operator=(exception && o) noexcept;
    public:     exception();
    public:     exception(const exception & o);
    public:     exception(exception && o) noexcept;
    public:     virtual ~exception();
    };
}

#include <novemberizing/exception.hp>

#endif // __NOVEMBERIZING__EXCEPTION__HH__
