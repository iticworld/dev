/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 10
 */

#ifndef   __NOVEMBERIZING__RANDOM__HH__
#define   __NOVEMBERIZING__RANDOM__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class random
    {
    protected:  static unsigned int __seed;
    protected:  static int __get();
    public:     template <typename T> static T get();
    public:     template <typename T> static T get(int limit);
    public:     random & operator=(const random & o);
    public:     random & operator=(random && o) noexcept;
    public:     random();
    public:     random(const random & o);
    public:     random(random && o) noexcept;
    public:     virtual ~random();
    };
}

#include <novemberizing/random.hp>

#endif // __NOVEMBERIZING__RANDOM__HH__
