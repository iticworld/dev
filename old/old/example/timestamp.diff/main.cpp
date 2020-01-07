
#include <novemberizing.hh>
#include <novemberizing/random.hh>

using namespace novemberizing;

static void print(const timestamp & o)
{
    printf("%ld.%09ld\n", o.second(), o.nanosecond());
}

int main()
{
    timestamp previous = timestamp::get();

    system::sleep(random::get<int64>(65536));

    timestamp v = timestamp::gap(previous);

    print(v);

    return 0;
}