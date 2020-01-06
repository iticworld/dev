#include <iostream>

static void division(int x, int y)
{
    int remain = x;
    int bits = 0;
    while(x != 0)
    {
        x = x >> 1;
        bits++;
    }
    int c = y << bits;
    int n = 0;
    for(int i = 0;i<bits;i++)
    {
        c = c >> 1;
        n = n << 1;
        remain = remain - c;
        if(remain > 0)
        {
            n |= 1;
        }
        else if(remain < 0)
        {
            remain = remain + c;
        }
    }
    printf("%d.%d\n", n, remain);
}

int main() {
    division(65536, 3);
    printf("%d\n", 65536 % 3);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}