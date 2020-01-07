/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 27.
 */

#ifndef   __NOVEMBERIZING__DESCRIPTOR__HH__
#define   __NOVEMBERIZING__DESCRIPTOR__HH__

#include <novemberizing/pointer.hh>

namespace novemberizing
{
    template <typename T>
    class descriptor
    {
    protected:  static T * allocate(const T & o);
    protected:  static T * release(T * o);
    protected:  static int32 close(const T & o);
    protected:  pointer<T> __v;
    public:     descriptor<T> & operator=(const descriptor<T> & o);
    public:     descriptor<T> & operator=(descriptor<T> && o) noexcept;
    public:     descriptor(const T & o);
    public:     descriptor(const T & o, function<T * (T *)> d);
    public:     descriptor();
    public:     descriptor(const descriptor<T> & o);
    public:     descriptor(descriptor<T> && o) noexcept;
    public:     virtual ~descriptor();
    };
}

#include <novemberizing/descriptor.hp>
#include <novemberizing/descriptor/integer.hp>

#endif // __NOVEMBERIZING__DESCRIPTOR__HH__
