/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__MOVE__HH__
#define   __NOVEMBERIZING__MOVE__HH__

namespace novemberizing
{
    template <typename T> struct ____remove_reference { typedef T type; };
    template <typename T> struct ____remove_reference<T &> { typedef T type; };
    template <typename T> struct ____remove_reference<T &&> { typedef T type; };

    template <typename T> constexpr typename ____remove_reference<T>::type && move(T && o) noexcept { return static_cast<typename ____remove_reference<T>::type &&>(o); }
}

#endif // __NOVEMBERIZING__MOVE__HH__
