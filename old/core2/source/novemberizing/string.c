/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#include <string.h>
#include <stdlib.h>

#include "../novemberizing.h"

_size __novemberizing_core_string_length(const char * s)
{
    return s != 0 ? strlen(s) : 0;
}

char * __novemberizing_core_string_new(const char * s)
{
    if(s != 0)
    {
        _size n = strlen(s);
        char * out = malloc(n + 1);
        strncpy(out, s, n);
        out[n] = 0;
        return out;
    }
    return 0;
}

char * __novemberizing_core_string_reset(char * destination, const char * s)
{
    if(s != 0)
    {
        _size n = strlen(s);
        char * out = realloc(destination, n + 1);
        strncpy(out, s, n);
        out[n] = 0;
        return out;
    }
    else
    {
        free(destination);
    }
    return 0;
}

_int32 __novemberizing_core_string_compare(const char * x, const char * y, _size n)
{
    if(x == 0)
    {
        return y == 0 ? 0 : -1;
    }
    else if(y == 0)
    {
        return 1;
    }
    else
    {
        return strncmp(x, y, n);
    }
}

