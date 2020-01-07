#include <stdio.h>
#include <time.h>

class example
{
public:     inline void hello(){ printf("hello\n"); }
public:     void world();
};

int main()
{
    struct timespec start;
    struct timespec end;
    struct timespec result;
    example x;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.world();

    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%09ld\n", result.tv_sec, result.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.hello();
    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%09ld\n", result.tv_sec, result.tv_nsec);

    return 0;
}

void example::world()
{
    printf("world\n");
}
