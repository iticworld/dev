/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#ifndef   __NOVEMBERIZING__RUNNABLE__HH__
#define   __NOVEMBERIZING__RUNNABLE__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class runnable
    {
    public:     virtual void run() = 0;
    public:     runnable & operator=(const runnable & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     runnable & operator=(runnable && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     runnable()
                {
                    FUNCTION_LOG("");
                }
    public:     runnable(const runnable & o)
                {
                    FUNCTION_LOG("");
                }
    public:     runnable(runnable && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     virtual ~runnable()
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__RUNNABLE__HH__
