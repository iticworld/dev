#include <novemberizing.h>

#include <stdio.h>
#include <errno.h>

int main(int argc, char ** argv)
{
    _int64 second = 0;
    _int64 nanosecond = 0;
    if(__novemberizing_core_timestamp_get(&second, &nanosecond) == 0)
    {
#ifdef    WIN32
        printf("timestamp: %lld.%09lld\n", second, nanosecond);
#else  // WIN32
        printf("timestamp: %ld.%09ld\n", second, nanosecond);
#endif // WIN32
    }
    else
    {
        printf("fail to __novemberizing_core_timestamp_get(...) caused by %d\n", errno);
    }
    return 0;
}

