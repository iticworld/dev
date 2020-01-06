/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__HH__
#define   __NOVEMBERIZING__HH__

#include <novemberizing.h>

namespace novemberizing
{
    namespace type
    {
        typedef __INT8_TYPE__       int8;
        typedef __INT16_TYPE__      int16;
        typedef __INT32_TYPE__      int32;
        typedef __INT64_TYPE__      int64;
        typedef __UINT8_TYPE__      uint8;
        typedef __UINT16_TYPE__     uint16;
        typedef __UINT32_TYPE__     uint32;
        typedef __UINT64_TYPE__     uint64;
        typedef __UINT8_TYPE__      byte;
        typedef char                character;
        typedef __SIZE_TYPE__       size;
        typedef void *              pointer;
        typedef double              float32;
        typedef long double         float64;
    }

    enum {
        success = 0,
        fail = -1
    };
}

#include <novemberizing/move.hh>

#endif // __NOVEMBERIZING__HH__
