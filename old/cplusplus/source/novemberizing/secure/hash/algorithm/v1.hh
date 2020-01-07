/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#ifndef   __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V1__HH__
#define   __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V1__HH__

#include <novemberizing/string.hh>
#include <novemberizing/bytes.hh>

namespace novemberizing
{
    namespace secure
    {
        namespace hash
        {
            namespace algorithm
            {
                class v1
                {
//                public:     static bytes from(const string & v);
                public:     static bytes from(const bytes & v);
                public:     v1 & operator=(const v1 & o);
                public:     v1 & operator=(v1 && o) noexcept;
                public:     v1();
                public:     v1(const v1 & o);
                public:     v1(v1 && o) noexcept;
                public:     virtual ~v1();
                };
            }
        }
    }
}

#include <novemberizing/secure/hash/algorithm/v1.hp>

#endif // __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V1__HH__
