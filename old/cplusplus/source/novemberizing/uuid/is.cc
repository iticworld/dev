/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 5
 */

#include "../uuid.hh"

namespace novemberizing
{
    bool uuid::is::v1(const uuid & o)
    {
        return version(o) == 1;
    }

    bool uuid::is::v2(const uuid & o)
    {
        return version(o) == 2;
    }

    bool uuid::is::v3(const uuid & o)
    {
        return version(o) == 3;
    }

    bool uuid::is::v4(const uuid & o)
    {
        return version(o) == 4;
    }

    bool uuid::is::v5(const uuid & o)
    {
        return version(o) == 5;
    }
}

