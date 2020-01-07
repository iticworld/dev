#include <iostream>
#include <novemberizing.hh>
#include <novemberizing/random.hh>

using namespace novemberizing;

const int max = 1024;

static void example_if()
{
    printf("if\n");
    timestamp start;
    timestamp end;
    for(int i = 0; i < max; i++)
    {
        int v = random::get<int>(65536);
        start = timestamp::get();
        if(v % 8 == 0)
        {
            if(v % 65536 == 0)
            {
                printf("operated value: %d\n", v);
            }
        }
        else
        {
            end = timestamp::gap(start);
            printf("%ld.%09ld\n", end.second(), end.nanosecond());
        }
    }
}

static void example_throw()
{
    printf("throw\n");
    timestamp start;
    timestamp end;
    for(int i = 0; i < max; i++)
    {
        int v = random::get<int>(65536);
        start = timestamp::get();
        try
        {
            if(v % 8 != 0)
            {
                throw v;
            }
            if(v % 65536 == 0)
            {
                printf("operated value: %d\n", v);
            }
        }
        catch(const int v)
        {
            end = timestamp::gap(start);
            printf("%ld.%09ld\n", end.second(), end.nanosecond());
        }
    }
}

int main()
{
    example_if();
    example_throw();
    return 0;
}