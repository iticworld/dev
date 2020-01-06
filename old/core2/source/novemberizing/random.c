/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#include <stdlib.h>
#include <time.h>

#include "../novemberizing.h"

static unsigned int __seed = (unsigned int)(-1);

_int32 __novemberizing_core_random_get()
{

#ifdef    WIN32
    if(__seed == (unsigned int)(-1))
    {
        __seed = (unsigned int)(time(0));
    }
    __seed = time(0) + time(0) % 3 + __seed;
    int v = (unsigned int) time(0) ^ __seed;
    return v >= 0 ? v : -v;  // NOLINT
#else  // WIN32
    if(__seed == (unsigned int)(-1))
    {
        __seed = (unsigned int)(time(0));
    }
    srand(__seed);
    return rand_r(&__seed);
#endif // WIN32
}

_uint32 __novemberizing_core_random_seed_get()
{
    return __seed;
}

