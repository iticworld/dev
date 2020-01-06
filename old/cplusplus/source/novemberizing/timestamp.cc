/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 19.
 */

#include <time.h>

#include "novemberizing/timestamp.hh"
#include "novemberizing/exception.hh"

namespace novemberizing
{
    timestamp::timestamp()
    {
#ifndef   WIN32
        struct timespec spec;
        if(clock_gettime(CLOCK_REALTIME, &spec) == 0)
        {
            __second = spec.tv_sec;
            __nanosecond = spec.tv_nsec;
        }
        else
        {
            throw exception();
        }
#endif // WIN32
    }
}

