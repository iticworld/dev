#include <novemberizing.h>

#include <stdio.h>

int main(int argc, char ** argv)
{
    for(int i = 0;i<64;i++)
    {
        printf("random: %d\n", __novemberizing_core_random_get());
    }

    printf("seed: %u\n", __novemberizing_core_random_seed_get());
    return 0;
}
