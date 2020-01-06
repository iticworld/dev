/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#include <string.h>
#include <stdlib.h>

#include "novemberizing.h"

void * __novemberizing_memory_allocate(nsize n)
{
    return malloc(n);
}

void * __novemberizing_memory_reallocate(void * p, nsize n)
{
    return realloc(p, n);
}

void * __novemberizing_memory_deallocate(void * p)
{
    if(p != 0)
    {
        free(p);
    }
    return 0;
}

void * __novemberizing_memory_copy(void * destination, const void * source, nsize n)
{
    return memcpy(destination, source, n);
}

void * __novemberizing_memory_move(void * destination, const void * source, nsize n)
{
    return memmove(destination, source, n);
}

void * __novemberizing_memory_fill(void * destination, int c, nsize n)
{
    return memset(destination, c, n);
}
