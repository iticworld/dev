/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#ifndef   __NOVEMBERIZING__RANDOM__HH__
#define   __NOVEMBERIZING__RANDOM__HH__

#include <novemberizing/exception.hh>

namespace novemberizing
{
    namespace random
    {
        template <typename T>
        T get()
        {
            return static_cast<T>(__novemberizing_random_get());
        }

        template <typename T>
        T get(type::uint32 limit)
        {
            if(limit == 0)
            {
                throw exception();  // NOLINT
            }
            return static_cast<T>(__novemberizing_random_get() % limit);
        }
    }
}

#endif // __NOVEMBERIZING__RANDOM__HH__
