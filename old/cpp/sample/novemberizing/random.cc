#include <novemberizing/random.hh>

using namespace novemberizing;

#include <cstdio>

int main(int argc, char ** argv)
{
    for(type::int32 i = 0; i < 8; i++)
    {
        printf("%d\n", random::get<type::int32>());
    }
    for(type::int32 i = 0; i < 8; i++)
    {
        printf("%d\n", random::get<type::int32>(64));
    }
    return 0;
}
