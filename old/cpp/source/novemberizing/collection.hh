/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__COLLECTION__HH__
#define   __NOVEMBERIZING__COLLECTION__HH__

#include <novemberizing/container.hh>

namespace novemberizing
{
    template <typename T>
    class collection : public container
    {
    public:     virtual bool add(const T & v) = 0;
    public:     virtual void add(const T & v, callback::pair<const T &, bool> f) = 0;
    public:     virtual bool add(T && v) = 0;
    public:     virtual void add(T && v, callback::pair<const T &, bool> f) = 0;
    public:     virtual bool del(const T & v) = 0;
    public:     virtual void del(const T & v, callback::pair<T &&, bool> f) = 0;
    public:     virtual bool exist(const T & v) const = 0;
    public:     virtual void exist(const T & v, callback::pair<const T &, bool> f) const = 0;
    public:     virtual void clear() = 0;
    public:     virtual void clear(callback::single<T &&> f) = 0;
    public:     virtual void each(callback::single<const T &> f) const = 0;
    public:     collection<T> & operator=(const collection<T> & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     collection<T> & operator=(collection<T> && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     collection()
                {
                    FUNCTION_LOG("");
                }
    public:     collection(const collection<T> & o)
                {
                    FUNCTION_LOG("");
                }
    public:     collection(collection<T> && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     ~collection() override
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__COLLECTION__HH__
