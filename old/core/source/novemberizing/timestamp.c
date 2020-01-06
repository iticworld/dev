/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#include <time.h>

#include "novemberizing.h"

int __novemberizing_timestamp_get(nint64 * second, nint64 * nanosecond)
{
    struct timespec spec;
    if(clock_gettime(CLOCK_REALTIME, &spec) == 0)
    {
        if(second != 0)
        {
            *second = spec.tv_sec;
        }
        if(nanosecond != 0)
        {
            *nanosecond = spec.tv_nsec;
        }
        return 0;
    }
    return -1;
}





