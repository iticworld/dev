/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 9.
 */

#ifndef   __NOVEMBERIZING__INTERNET_ADDRESS__HH__
#define   __NOVEMBERIZING__INTERNET_ADDRESS__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    namespace internet
    {
        class address
        {
        public:     class to
                    {
                    public:     to & operator=(const to & o);
                    public:     to & operator=(to && o) noexcept;
                    public:     to();
                    public:     to(const to & o);
                    public:     to(to && o) noexcept;
                    public:     virtual ~to();
                    };
        public:     address & operator=(const address & o);
        public:     address & operator=(address && o) noexcept;
        public:     address();
        public:     address(const address & o);
        public:     address(address && o) noexcept;
        public:     virtual ~address();
        };
    }
}

#endif // __NOVEMBERIZING__INTERNET_ADDRESS__HH__
