/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#ifndef   __NOVEMBERIZING__CALLBACK__HH__
#define   __NOVEMBERIZING__CALLBACK__HH__

#include <novemberizing/function.hh>

namespace novemberizing
{
    namespace callback
    {
        template <typename A>
        using single = function<void (A)>;

        template <typename A, typename B>
        using pair = function<void (A, B)>;

        template <typename A, typename B, typename C>
        using triple = function<void (A, B, C)>;
    }
}

#endif // __NOVEMBERIZING__CALLBACK__HH__
