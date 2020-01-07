/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__H__
#define   __NOVEMBERIZING__H__

#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus


typedef __INT8_TYPE__       nint8;
typedef __INT16_TYPE__      nint16;
typedef __INT32_TYPE__      nint32;
typedef __INT64_TYPE__      nint64;
typedef __UINT8_TYPE__      nuint8;
typedef __UINT16_TYPE__     nuint16;
typedef __UINT32_TYPE__     nuint32;
typedef __UINT64_TYPE__     nuint64;
typedef char                nchar;
typedef __UINT8_TYPE__      nbyte;
typedef __SIZE_TYPE__       nsize;
typedef void *              npointer;

#define novemberizing_log_type_function     (0x00000001U << 0U)
#define novemberizing_log_type_error        (0x00000001U << 1U)
#define novemberizing_log_type_warning      (0x00000001U << 2U)
#define novemberizing_log_type_caution      (0x00000001U << 3U)
#define novemberizing_log_type_notice       (0x00000001U << 4U)
#define novemberizing_log_type_information  (0x00000001U << 5U)
#define novemberizing_log_type_debug        (0x00000001U << 6U)
#define novemberizing_log_type_verbose      (0x00000001U << 7U)

#define FUNCTION_LOG(format, ...)       do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_function,      \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define ERROR_LOG(format, ...)          do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_error,         \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define WARNING_LOG(format, ...)        do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_warning,       \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define CAUTION_LOG(format, ...)        do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_caution,       \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define NOTICE_LOG(format, ...)         do {                         \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_notice,        \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define INFORMATION_LOG(format, ...)    do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_information,   \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define DEBUG_LOG(format, ...)          do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_debug,         \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

#define VERBOSE_LOG(format, ...)        do {                        \
    nint64 second = 0;                                              \
    nint64 nanosecond = 0;                                          \
    __novemberizing_timestamp_get(&second, &nanosecond);            \
    __novemberizing_log_write(novemberizing_log_type_verbose,       \
                              second,                               \
                              nanosecond,                           \
                              __FILE__,                             \
                              __LINE__,                             \
                              __func__,                             \
                              format, ##__VA_ARGS__);               \
} while(0)

extern int __novemberizing_timestamp_get(nint64 * second, nint64 * nanosecond);
extern void __novemberizing_log_write(nuint32 type, nint64 second, nint64 nanosecond, const char * file, nint32 line, const char * function, const char * format, ...);
extern void * __novemberizing_memory_allocate(nsize n);
extern void * __novemberizing_memory_reallocate(void * p, nsize n);
extern void * __novemberizing_memory_deallocate(void * p);
extern void * __novemberizing_memory_copy(void * destination, const void * source, nsize n);
extern void * __novemberizing_memory_move(void * destination, const void * source, nsize n);
extern void * __novemberizing_memory_fill(void * destination, int c, nsize n);

extern nsize __novemberizing_string_length(const char * s);
extern nint32 __novemberizing_string_compare(const char * x, const char * y, nsize n);
extern nint32 __novemberizing_random_get();


#ifdef    __cplusplus
}
#endif // __cplusplus

#endif // __NOVEMBERIZING__H__
