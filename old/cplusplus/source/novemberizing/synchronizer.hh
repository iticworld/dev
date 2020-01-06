/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#ifndef   __NOVEMBERIZING__SYNCHRONIZER__HH__
#define   __NOVEMBERIZING__SYNCHRONIZER__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class synchronizer
    {
    public:     virtual int32 lock() const;
    public:     virtual int32 unlock() const;
    public:     virtual int32 wait() const;
    public:     virtual int32 wait(int64 nanosecond) const;
    public:     virtual int32 wakeup() const;
    public:     virtual int32 wakeup(bool all) const;
    public:     synchronizer & operator=(const synchronizer & o);
    public:     synchronizer & operator=(synchronizer && o) noexcept;
    public:     synchronizer();
    public:     synchronizer(const synchronizer & o);
    public:     synchronizer(synchronizer && o) noexcept;
    public:     virtual ~synchronizer();
    };
}

#include <novemberizing/synchronizer.hp>

#endif // __NOVEMBERIZING__SYNCHRONIZER__HH__
