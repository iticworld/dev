#ifndef   __NOVEMBERIZING__HH__
#define   __NOVEMBERIZING__HH__

#include <sys/types.h>
#include <stdint.h>
#include <time.h>

namespace novemberizing {

enum {
    Success = 0L,
    Fail = -1L,
    Invalid = -1L,
    Infinite = -1L,
};

namespace type {

typedef int8_t      int8;
typedef uint8_t     uint8;
typedef int16_t     int16;
typedef uint16_t    uint16;
typedef int32_t     int32;
typedef uint32_t    uint32;
typedef int64_t     int64;
typedef uint64_t    uint64;

typedef time_t      second;
typedef long        nano;

typedef size_t      size;

}

}

#endif // __NOVEMBERIZING__HH__
