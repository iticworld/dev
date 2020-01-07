/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 22.
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>

#include "util.h"

void random_init()
{
    srand((unsigned int) time(NULL));
}

int random_get(int bound)
{
    if(bound > 0)
    {
        return rand() % bound;
    }
    else
    {
        printf("bound <= 0\n");
    }
    return 0;
}

int timestamp_get(struct timestamp * p)
{
    if(p != NULL)
    {
        struct timespec v;
        if(clock_gettime(CLOCK_REALTIME, &v) == 0)
        {
            p->second = v.tv_sec;
            p->nanosecond = v.tv_nsec;
            return success;
        }
        else
        {
            printf("fail to clock_gettime(CLOCK_REALTIME, &v) caused by %d\n", errno);
        }
    }
    else
    {
        printf("p == null\n");
    }
    return fail;
}

void timestamp_out(struct timestamp * p)
{
    if(p != NULL)
    {
#ifdef    __EMSCRIPTEN__
        printf("%lld.%09lld\n", p->second, p->nanosecond);
#else  // __EMSCRIPTEN__
        printf("%ld.%09ld\n", p->second, p->nanosecond);
#endif // __EMSCRIPTEN__
    }
    else
    {
        printf("p == null\n");
    }
}

int timestamp_gap(struct timestamp * p, struct timestamp * previous)
{
    if(p != NULL && previous != NULL)
    {
        struct timestamp current = {};
        if(timestamp_get(&current) == success)
        {
            p->second = current.second - previous->second;
            p->nanosecond = current.nanosecond - previous->nanosecond;
#ifdef    __EMSCRIPTEN__
            integer64 n = llabs(p->nanosecond);
#else  // __EMSCRIPTEN__
            integer64 n = labs(p->nanosecond);
#endif // __EMSCRIPTEN__
            if(p->nanosecond >= 0)
            {
                p->second += (n / 1000000000);
                p->nanosecond = (n % 1000000000);
            }
            else
            {
                p->second -= (n / 1000000000);
                p->nanosecond = (n % 1000000000);
                p->second -= 1;
                p->nanosecond = 1000000000 - p->nanosecond;
            }
            return success;
        }
        else
        {
            printf("fail to timestamp_get(&current)\n");
        }
    }
    else
    {
        printf("p == null || previous == NULL\n");
    }
    return fail;
}
