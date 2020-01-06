/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__FUNCTION__HH__
#define   __NOVEMBERIZING__FUNCTION__HH__

#include <functional>

namespace novemberizing
{
    template <typename T> using function = std::function<T>;
}

#endif // __NOVEMBERIZING__FUNCTION__HH__
