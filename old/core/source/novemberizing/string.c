/**
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#include <string.h>

#include "novemberizing.h"

nsize __novemberizing_string_length(const char * s)
{
    return strlen(s);
}

nint32 __novemberizing_string_compare(const char * x, const char * y, nsize n)
{
    return strncmp(x, y, n);
}

