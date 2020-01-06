#include <novemberizing.hh>

using namespace novemberizing;

static void print(const integer & x)
{
    printf("%s", x.plus() ? "" : "-");
    for(uint64 i = x.size() - 1; i != (uint64) -1;i--)
    {
        printf("%016lX", x.at(i));
    }
    printf("\n");
}

int main() {
    integer x = 0xFFFFFFFF000000F1L;
    integer y = 65531;
    x *= y;
    print(x);
    for(int j = 0 ; j < 65531; j++)
    {
        x.minus(0xFFFFFFFF000000F1);
    }
    print(x);
    for(int j = 0 ; j < 65531; j++)
    {
        x.plus(0xFFFFFFFF000000F1);
    }
    print(x);
    return 0;
}
