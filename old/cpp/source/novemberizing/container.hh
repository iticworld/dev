/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__CONTAINER__HH__
#define   __NOVEMBERIZING__CONTAINER__HH__

#include <novemberizing.hh>
#include <novemberizing/callback.hh>
#include <novemberizing/sync.hh>
#include <novemberizing/exception.hh>

namespace novemberizing
{
    class container : public sync
    {
    public:     virtual type::size size() const = 0;
    public:     virtual void size(callback::single<type::size> f) const = 0;
    public:     virtual bool empty() const = 0;
    public:     virtual void empty(callback::single<bool> f) const = 0;
    public:     container & operator=(const container & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     container & operator=(container && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     container()
                {
                    FUNCTION_LOG("");
                }
    public:     container(const container & o)
                {
                    FUNCTION_LOG("");
                }
    public:     container(container && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     ~container() override
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__CONTAINER__HH__
