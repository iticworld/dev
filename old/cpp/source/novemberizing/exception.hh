/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__EXCEPTION__HH__
#define   __NOVEMBERIZING__EXCEPTION__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class exception
    {
    public:     exception & operator=(const exception & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     exception & operator=(exception && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     exception()
                {
                    FUNCTION_LOG("");
                }
    public:     exception(const exception & o)
                {
                    FUNCTION_LOG("");
                }
    public:     exception(exception && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     virtual ~exception()
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__EXCEPTION__HH__
