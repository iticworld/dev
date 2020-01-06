/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 21.
 */

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

#include "time.h"

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
        printf("%ld.%09ld\n", p->second, p->nanosecond);
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
            integer64 n = labs(p->nanosecond);
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
