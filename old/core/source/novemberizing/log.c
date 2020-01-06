/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#include <stdarg.h>
#include <stdio.h>

#include "novemberizing.h"


static const char * __novemberizing_log_type_to_string(nuint32 type)
{
    switch(type)
    {
        case novemberizing_log_type_function: return "function";
        case novemberizing_log_type_error: return "error";
        case novemberizing_log_type_warning: return "warning";
        case novemberizing_log_type_caution: return "caution";
        case novemberizing_log_type_notice: return "notice";
        case novemberizing_log_type_information: return "information";
        case novemberizing_log_type_debug: return "debug";
        case novemberizing_log_type_verbose: return "verbose";
        default: return "unknown";
    }
}

void __novemberizing_log_write(nuint32 type, nint64 second, nint64 nanosecond, const char * file, nint32 line, const char * function, const char * format, ...)
{
//    char str[4096];
//    va_list ap;
//    va_start(ap, format);
//    vsnprintf(str, 4096, format, ap);
//    va_end(ap);
//
//    printf("[%s] %ld.%09ld %s (%s:%d/%s)\n", __novemberizing_log_type_to_string(type)
//            , second
//            , nanosecond
//            , str
//            , file
//            , line
//            , function);
}
