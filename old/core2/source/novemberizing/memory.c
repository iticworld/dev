/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#include <stdlib.h>
#include <string.h>

#include "../novemberizing.h"

void * __novemberizing_core_memory_allocate(_size n)
{
    if(n > 0)
    {
        return malloc(n);
    }
    else
    {
        return 0;
    }
}

void * __novemberizing_core_memory_reallocate(void * p, _size n)
{
    if(n > 0)
    {
        return realloc(p, n);
    }
    else
    {
        free(p);
        return 0;
    }
}

void * __novemberizing_core_memory_deallocate(void * p)
{
    free(p);
    return 0;
}

void * __novemberizing_core_memory_copy(void * destination, const void * source, _size n)
{
    if(destination != 0 && source != 0 && n > 0)
    {
        return memcpy(destination, source, n);
    }
    return 0;
}

void * __novemberizing_core_memory_move(void * destination, const void * source, _size n)
{
    if(destination != 0 && source != 0 && n > 0)
    {
        return memmove(destination, source, n);
    }
    return 0;
}

void * __novemberizing_core_memory_fill(void * destination, int c, _size n)
{
    if(destination != 0 && n > 0)
    {
        return memset(destination, c, n);
    }
    return 0;
}

