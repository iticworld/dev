/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 07. 16.
 */

#ifndef   __NOVEMBERIZING__POINTER__HH__
#define   __NOVEMBERIZING__POINTER__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    template <typename T>
    class pointer
    {
    private:    T * __value;
    private:    int64 * __count;
    private:    function<T * (T *)> __delete;
    public:     int64 count() const;
    protected:  virtual void clear();
    public:     T * p();
    public:     const T * p() const;
    public:     T & v();
    public:     const T & v() const;
    public:     T * operator->();
    public:     const T * operator->() const;
    public:     T & operator*();
    public:     const T & operator*() const;
    public:     pointer & operator=(const pointer & o);
    public:     pointer & operator=(pointer && o) noexcept;
    public:     pointer();
    public:     pointer(T * p);
    public:     pointer(T * p, function<T * (T *)> d);
    public:     pointer(const pointer & o);
    public:     pointer(pointer && o) noexcept;
    public:     virtual ~pointer();
    };
}

#include <novemberizing/pointer.hp>

#endif // __NOVEMBERIZING__POINTER__HH__
