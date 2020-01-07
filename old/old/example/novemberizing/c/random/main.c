#include <stdio.h>
#include <novemberizing/random.h>

int main()
{
    random_init();
    for(int i = 0; i < 64; i++)
    {
        printf("random number: %d\n", random_get(100));
    }
    return 0;
}