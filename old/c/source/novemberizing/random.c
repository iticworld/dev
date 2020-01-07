/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 21.
 */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "random.h"

void random_init()
{
    srand((unsigned int) time(NULL));
}

int random_get(int bound)
{
    if(bound > 0)
    {
        return rand() % bound;
    }
    else
    {
        printf("bound <= 0\n");
    }
    return 0;
}

