/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#ifndef   __NOVEMBERIZING__LIST__HH__
#define   __NOVEMBERIZING__LIST__HH__

#include <novemberizing/collection.hh>

namespace novemberizing
{
    template <typename T>
    class list : public collection<T>
    {
    public:     list<T> & operator=(const list<T> & o)
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     list<T> & operator=(list<T> && o) noexcept
                {
                    FUNCTION_LOG("");
                    return *this;
                }
    public:     list()
                {
                    FUNCTION_LOG("");
                }
    public:     list(const list<T> & o)
                {
                    FUNCTION_LOG("");
                }
    public:     list(list<T> && o) noexcept
                {
                    FUNCTION_LOG("");
                }
    public:     ~list() override
                {
                    FUNCTION_LOG("");
                }
    };
}

#endif // __NOVEMBERIZING__LIST__HH__
