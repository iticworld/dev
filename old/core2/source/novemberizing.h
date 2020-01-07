/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 19.
 */

#ifndef   __NOVEMBERIZING__H__
#define   __NOVEMBERIZING__H__

#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

typedef __INT8_TYPE__       _int8;
typedef __INT16_TYPE__      _int16;
typedef __INT32_TYPE__      _int32;
typedef __INT64_TYPE__      _int64;
typedef __UINT8_TYPE__      _uint8;
typedef __UINT16_TYPE__     _uint16;
typedef __UINT32_TYPE__     _uint32;
typedef __UINT64_TYPE__     _uint64;
typedef __SIZE_TYPE__       _size;
typedef char                _char;
typedef unsigned char       _byte;
typedef void *              _handle;

extern int __novemberizing_core_timestamp_get(_int64 * second, _int64 * nanosecond);

extern void * __novemberizing_core_memory_allocate(_size n);
extern void * __novemberizing_core_memory_reallocate(void * p, _size n);
extern void * __novemberizing_core_memory_deallocate(void * p);
extern void * __novemberizing_core_memory_copy(void * destination, const void * source, _size n);
extern void * __novemberizing_core_memory_move(void * destination, const void * source, _size n);
extern void * __novemberizing_core_memory_fill(void * destination, int c, _size n);

extern _size __novemberizing_core_string_length(const char * s);
extern char * __novemberizing_core_string_new(const char * s);
extern char * __novemberizing_core_string_reset(char * destination, const char * s);
extern _int32 __novemberizing_core_string_compare(const char * x, const char * y, _size n);

extern _int32 __novemberizing_core_random_get();
extern _uint32 __novemberizing_core_random_seed_get();

extern void __novemberizing_core_log_write(_uint32 type, _int64 second, _int64 nanosecond, const char * file, _int32 line, const char * function, const char * format, ...);

#define __novemberizing_core_log_type_function      (0x00000001U << 0U)
#define __novemberizing_core_log_type_error         (0x00000001U << 1U)
#define __novemberizing_core_log_type_warning       (0x00000001U << 2U)
#define __novemberizing_core_log_type_caution       (0x00000001U << 3U)
#define __novemberizing_core_log_type_notice        (0x00000001U << 4U)
#define __novemberizing_core_log_type_information   (0x00000001U << 5U)
#define __novemberizing_core_log_type_debug         (0x00000001U << 6U)
#define __novemberizing_core_log_type_verbose       (0x00000001U << 7U)

#define FUNCTION_LOG(format, ...)       do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_function,      \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define ERROR_LOG(format, ...)          do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_error,         \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define WARNING_LOG(format, ...)        do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_warning,       \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define CAUTION_LOG(format, ...)        do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_caution,       \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define NOTICE_LOG(format, ...)         do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_notice,        \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define INFORMATION_LOG(format, ...)    do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_information,   \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define DEBUG_LOG(format, ...)          do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_debug,         \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

#define VERBOSE_LOG(format, ...)        do {                                    \
    _int64 second = 0;                                                          \
    _int64 nanosecond = 0;                                                      \
    __novemberizing_core_timestamp_get(&second, &nanosecond);                   \
    __novemberizing_core_log_write(__novemberizing_core_log_type_verbose,       \
                              second,                                           \
                              nanosecond,                                       \
                              __FILE__,                                         \
                              __LINE__,                                         \
                              __func__,                                         \
                              format, ##__VA_ARGS__);                           \
} while(0)

typedef void * (* __novemberizing_core_thread_routine)(void *);
extern _handle __novemberizing_core_thread_new();
extern _int32 __novemberizing_core_thread_start(_handle h, __novemberizing_core_thread_routine f, void * param);
extern _int32 __novemberizing_core_thread_stop(_handle h);
extern _handle __novemberizing_core_thread_free(_handle h);

#ifdef    __cplusplus
}
#endif // __cplusplus

#endif // __NOVEMBERIZING__H__
