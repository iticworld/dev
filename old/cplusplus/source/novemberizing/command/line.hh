/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__COMMAND_LINE__HH__
#define   __NOVEMBERIZING__COMMAND_LINE__HH__

#include <novemberizing/input.hh>

namespace novemberizing
{
    namespace command
    {
        class line : public input
        {
        public:     line & operator=(const line & o);
        public:     line & operator=(line && o) noexcept;
        public:     line();
        public:     line(const line & o);
        public:     line(line && o) noexcept;
        public:     ~line() override;
        };
    }
}

#include <novemberizing/command/line.hp>

#endif // __NOVEMBERIZING__COMMAND_LINE__HH__
