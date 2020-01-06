/**
 *
 * @author      novemberizing <developer@novemberizing.net>
 * @since       0.0.1
 * @date        2018. 6. 3.
 */

#ifndef   __NOVEMBERIZING__HH__
#define   __NOVEMBERIZING__HH__

#include <novemberizing/function.hp>

namespace novemberizing
{
    typedef __INT8_TYPE__       int8;
    typedef __INT16_TYPE__      int16;
    typedef __INT32_TYPE__      int32;
    typedef __INT64_TYPE__      int64;
    typedef __UINT8_TYPE__      uint8;
    typedef __UINT16_TYPE__     uint16;
    typedef __UINT32_TYPE__     uint32;
    typedef __UINT64_TYPE__     uint64;
    typedef float               float32;    /** check float 32 */
    typedef double              float64;    /** check float 64 */
    typedef unsigned char       byte;

    const int32 success = 0;
    const int32 fail = -1;
    const int32 invalid = -1;


}

#include <novemberizing/core.hh>

//#include <novemberizing/string.hh>
//#include <novemberizing/move.hp>
//#include <novemberizing/capacity.hp>
//#include <novemberizing/system.hp>
//#include <novemberizing/core/memory.hp>
//#include <novemberizing/endian.hp>
//#include <novemberizing/integer.hp>
//#include <novemberizing/integer/to.hp>
//#include <novemberizing/integer/is.hp>
//#include <novemberizing/integer/add.hp>
//#include <novemberizing/bytes.hp>
//#include <novemberizing/bytes/to.hp>
//#include <novemberizing/timestamp.hp>
//#include <novemberizing/exception.hp>
//#include <novemberizing/pointer.hp>

#endif // __NOVEMBERIZING__HH__
