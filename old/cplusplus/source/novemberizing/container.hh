/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#ifndef   __NOVEMBERIZING__CONTAINER__HH__
#define   __NOVEMBERIZING__CONTAINER__HH__

#include <novemberizing.hh>
#include <novemberizing/synchronizer.hh>
#include <novemberizing/exception.hh>

namespace novemberizing
{
    class container
    {
    protected:  static const uint64 max = (uint64)(-1);
    protected:  static const uint64 eop = (uint64)(-1);
    protected:  static const uint64 page = (uint64)(64);
    public:     template <typename T> class base
                {
                public:     class accessor
                            {
                            public:     static uint64 previous(container::base<T> * p, uint64 i);
                            public:     static uint64 next(container::base<T> * p, uint64 i);
                            public:     static T & reference(container::base<T> * p, uint64 i);
                            public:     static T * pointer(container::base<T> * p, uint64 i);
                            public:     accessor & operator=(const accessor & o);
                            public:     accessor & operator=(accessor && o) noexcept;
                            public:     accessor();
                            public:     accessor(const accessor & o);
                            public:     accessor(accessor && o) noexcept;
                            public:     virtual ~accessor();
                            };
                protected:  virtual uint64 previous(uint64 i) = 0;
                protected:  virtual uint64 next(uint64 i) = 0;
                protected:  virtual T & reference(uint64 i) = 0;
                protected:  virtual T * pointer(uint64 i) = 0;
                public:     base<T> & operator=(const base<T> & o);
                public:     base<T> & operator=(base<T> && o) noexcept;
                public:     base();
                public:     base(const base<T> & o);
                public:     base(base<T> && o) noexcept;
                public:     virtual ~base();
                };
    protected:  synchronizer * __synchronizer;
    public:     virtual int32 lock() const;
    public:     virtual int32 unlock() const;
    public:     virtual int32 wait() const;
    public:     virtual int32 wait(int64 nanosecond) const;
    public:     virtual int32 wakeup() const;
    public:     virtual int32 wakeup(bool all) const;
    public:     virtual uint64 size() const = 0;
    public:     virtual void size(function<void (uint64)> f) const = 0;
    public:     virtual bool empty() const = 0;
    public:     virtual void empty(function<void (bool)> f) const = 0;
    public:     container & operator=(const container & o);
    public:     container & operator=(container && o) noexcept;
    public:     container();
    public:     container(const container & o);
    public:     container(container && o) noexcept;
    public:     virtual ~container();
    };
}

#include <novemberizing/container.hp>
#include <novemberizing/container/base.hp>
#include <novemberizing/container/base/accessor.hp>

#endif // __NOVEMBERIZING__CONTAINER__HH__
