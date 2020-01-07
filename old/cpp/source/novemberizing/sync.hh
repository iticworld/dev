/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__SYNC__HH__
#define   __NOVEMBERIZING__SYNC__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class sync
    {
    public:     virtual type::int32 lock() const { return success; }
    public:     virtual type::int32 unlock() const { return success; }
    public:     virtual type::int32 wait() const { return success; }
    public:     virtual type::int32 wait(type::int64 nanosecond) const { return success; }
    public:     virtual type::int32 wakeup() const { return success; }
    public:     virtual type::int32 wakeup(bool all) const { return success; }
    public:     sync & operator=(const sync & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     sync & operator=(sync && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     sync()
                {
                    FUNCTION_LOG("");
                }
    public:     sync(const sync & o)
                {
                    FUNCTION_LOG("");
                }
    public:     sync(sync && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     virtual ~sync()
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__SYNC__HH__
