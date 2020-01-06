/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#include <stdlib.h>
#include <time.h>

#include "novemberizing.h"

static unsigned int __seed = (unsigned int)(-1);

nint32 __novemberizing_random_get()
{
    if(__seed == (nuint32)(-1))
    {
        srand(__seed = (unsigned int) time(0));
    }
    return rand_r(&__seed);
}
