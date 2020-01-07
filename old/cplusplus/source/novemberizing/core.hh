/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__CORE__HH__
#define   __NOVEMBERIZING__CORE__HH__

#include <novemberizing.hh>
#include <novemberizing/core/memory.hh>

namespace novemberizing
{
    class system
    {
//    public:     static bytes mac();
    public:     static int32 sleep(int64 unisecond);
    public:     system & operator=(const system & o);
    public:     system & operator=(system && o) noexcept;
    public:     system();
    public:     system(const system & o);
    public:     system(system && o) noexcept;
    public:     virtual ~system();
    };

    class endian
    {
    public:     enum type
        {
            little = 0,
            big = 1
        };
    public:     typedef enum type type;
    public:     static endian::type get();
    public:     static uint16 convert(uint16 v);
    public:     static uint32 convert(uint32 v);
    public:     static uint64 convert(uint64 v);
    public:     static int16 convert(int16 v);
    public:     static int32 convert(int32 v);
    public:     static int64 convert(int64 v);
    public:     endian & operator=(const endian & o);
    public:     endian & operator=(endian && o) noexcept;
    public:     endian();
    public:     endian(const endian & o);
    public:     endian(endian && o) noexcept;
    public:     virtual ~endian();
    };
}

#include <novemberizing/core.hp>
#include <novemberizing/system.hp>
#include <novemberizing/endian.hp>

#endif // __NOVEMBERIZING__CORE__HH__
