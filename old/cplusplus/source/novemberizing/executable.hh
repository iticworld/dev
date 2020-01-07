/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__EXECUTABLE__HH__
#define   __NOVEMBERIZING__EXECUTABLE__HH__

#include <novemberizing/input.hh>
#include <novemberizing/output.hh>
#include <novemberizing/function.hh>

namespace novemberizing
{
    class executable
    {
    public:     virtual void execute(const input & i, function<void (output &&)> f) = 0;
    public:     virtual void execute(input && i, function<void (output &&)> f) = 0;
    public:     executable & operator=(const executable & o);
    public:     executable & operator=(executable && o) noexcept;
    public:     executable();
    public:     executable(const executable & o);
    public:     executable(executable && o) noexcept;
    public:     virtual ~executable();
    };
}

#include <novemberizing/executable.hp>

#endif // __NOVEMBERIZING__EXECUTABLE__HH__
