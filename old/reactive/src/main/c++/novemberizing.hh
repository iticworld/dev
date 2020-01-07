#ifndef   __NOVEMBERIZING__HH__
#define   __NOVEMBERIZING__HH__

#include <sys/types.h>
#include <stdint.h>

#include <time.h>

namespace novemberizing {

enum {
    Success = 0L,
    Fail = -1L,
    Infinite = -1L,
    Invalid = -1L,
};

namespace type {

typedef long nano;
typedef time_t second;

typedef int8_t          int8;
typedef uint8_t         uint8;
typedef int16_t         int16;
typedef uint16_t        uint16;
typedef int32_t         int32;
typedef uint32_t        uint32;
typedef int64_t         int64;
typedef uint64_t        uint64;

typedef size_t          size;
typedef unsigned char   byte;

}

}

#ifdef WIN32

#include <windows.h>
DWORD pthread_self() { return GetCurrentThreadId(); }

#endif // WIN32

#endif // __NOVEMBERIZING__CONSTANT__HH__
