/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#ifndef   __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V2__HH__
#define   __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V2__HH__

#include <novemberizing/exception.hh>
#include <novemberizing/bytes.hh>

namespace novemberizing
{
    namespace secure
    {
        namespace hash
        {
            namespace algorithm
            {
                class v2
                {
                public:     static bytes from(const bytes & v);
//                public:     static bytes from(const string & v);
                public:     v2 & operator=(const v2 & o);
                public:     v2 & operator=(v2 && o) noexcept;
                public:     v2();
                public:     v2(const v2 & o);
                public:     v2(v2 && o) noexcept;
                public:     virtual ~v2();
                };
            }
        }
    }
}

#include <novemberizing/secure/hash/algorithm/v2.hp>

#endif // __NOVEMBERIZING__SECURE_HASH_ALGORITHM_V2__HH__
