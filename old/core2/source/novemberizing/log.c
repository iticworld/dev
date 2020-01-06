/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#include <stdarg.h>
#include <stdio.h>

#include "novemberizing.h"

static const char * __novemberizing_core_log_type_to_string(_uint32 type)
{
    switch(type)
    {
        case __novemberizing_core_log_type_function: return "function";
        case __novemberizing_core_log_type_error: return "error";
        case __novemberizing_core_log_type_warning: return "warning";
        case __novemberizing_core_log_type_caution: return "caution";
        case __novemberizing_core_log_type_notice: return "notice";
        case __novemberizing_core_log_type_information: return "information";
        case __novemberizing_core_log_type_debug: return "debug";
        case __novemberizing_core_log_type_verbose: return "verbose";
        default: return "unknown";
    }
}

void __novemberizing_core_log_write(_uint32 type, _int64 second, _int64 nanosecond, const char * file, _int32 line, const char * function, const char * format, ...)
{
    (void)(__novemberizing_core_log_type_to_string);
    (void)(type);
    (void)(second);
    (void)(nanosecond);
    (void)(file);
    (void)(line);
    (void)(function);
    (void)(format);
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
