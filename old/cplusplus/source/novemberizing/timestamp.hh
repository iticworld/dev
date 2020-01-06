/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 07. 16.
 */

#ifndef   __NOVEMBERIZING__TIMESTAMP__HH__
#define   __NOVEMBERIZING__TIMESTAMP__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class timestamp
    {
    public:     static timestamp get();
    public:     static timestamp gap(const timestamp & y);
    protected:  int64 __second;
    protected:  int64 __nanosecond;
    public:     int64 second() const;
    public:     int64 nanosecond() const;
    public:     void second(int64 v);
    public:     void nanosecond(int64 v);
    public:     void set(int64 second, int64 nanosecond);
    public:     void set(const timestamp & o);
    public:     void set(timestamp && o);
    public:     timestamp & add(const timestamp & o);
    public:     timestamp & add(timestamp && o);
    public:     timestamp & sub(const timestamp & o);
    public:     timestamp & sub(timestamp && o);
    public:     timestamp & operator=(const timestamp & o);
    public:     timestamp & operator=(timestamp && o) noexcept;
    public:     timestamp & operator+=(const timestamp & o);
    public:     timestamp & operator+=(timestamp && o);
    public:     timestamp & operator-=(const timestamp & o);
    public:     timestamp & operator-=(timestamp && o);
    public:     timestamp(int64 second, int64 nanosecond);
    public:     timestamp();
    public:     timestamp(const timestamp & o);
    public:     timestamp(timestamp && o) noexcept;
    public:     virtual ~timestamp();
    };

    inline timestamp operator+ (const timestamp & x, const timestamp & y);
    inline timestamp operator- (const timestamp & x, const timestamp & y);
    inline bool      operator==(const timestamp & x, const timestamp & y);
    inline bool      operator!=(const timestamp & x, const timestamp & y);
    inline bool      operator< (const timestamp & x, const timestamp & y);
    inline bool      operator<=(const timestamp & x, const timestamp & y);
    inline bool      operator> (const timestamp & x, const timestamp & y);
    inline bool      operator>=(const timestamp & x, const timestamp & y);
}

#include <novemberizing/timestamp.hp>

#endif // __NOVEMBERIZING__TIMESTAMP__HH__
