/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#ifdef    WIN32
#include <windows.h>
#else  // WIN32
#include <time.h>
#endif // WIN32

#include "../novemberizing.h"

int __novemberizing_core_timestamp_get(_int64 * second, _int64 * nanosecond)
{
#ifdef    WIN32
    const INT64 UNIX_TIME_START = 0x019DB1DED53E8000;
    const INT64 TICKS_PER_SECOND = 10000000;
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    LARGE_INTEGER integer;
    integer.LowPart = ft.dwLowDateTime;
    integer.HighPart = ft.dwHighDateTime;
    if(second)
    {
        *second = (integer.QuadPart - UNIX_TIME_START) / TICKS_PER_SECOND;
    }
    if(nanosecond)
    {
        *nanosecond = ((integer.QuadPart - UNIX_TIME_START) % TICKS_PER_SECOND) * 100;
    }
    return 0;
#else  // WIN32
    struct timespec spec;
    if(clock_gettime(CLOCK_REALTIME, &spec) == 0)
    {
        if(second)
        {
            *second = spec.tv_sec;
        }
        if(nanosecond)
        {
            *nanosecond = spec.tv_nsec;
        }
        return 0;
    }
#endif // WIN32
    return -1;
}

