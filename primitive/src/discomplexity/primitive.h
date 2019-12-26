#ifndef   __DISCOMPLEXITY__PRIMITIVE__H__
#define   __DISCOMPLEXITY__PRIMITIVE__H__

#include <discomplexity.h>

typedef uint64 container_t;

struct __primitive_t
{
  uint32 type;
  container_t container;
};

typedef struct __primitive_t primitive_t;

#define PRIMITIVE_TYPE_NONE     0
#define PRIMITIVE_TYPE_INT8     1
#define PRIMITIVE_TYPE_INT16    2
#define PRIMITIVE_TYPE_INT32    3
#define PRIMITIVE_TYPE_INT64    4
#define PRIMITIVE_TYPE_UINT8    5
#define PRIMITIVE_TYPE_UINT16   6
#define PRIMITIVE_TYPE_UINT32   7
#define PRIMITIVE_TYPE_UINT64   8
#define PRIMITIVE_TYPE_STRING   9

#define PRIMITIVE_NULL          { PRIMITIVE_TYPE_NONE, 0 }

extern const char * primitive_type_string_get(const primitive_t * p);

extern primitive_t * primitive_del(primitive_t * o, uint32 flags);

extern primitive_t * primitive_int8_new(primitive_t * o, int8 v);
extern primitive_t * primitive_int16_new(primitive_t * o, int16 v);
extern primitive_t * primitive_int32_new(primitive_t * o, int32 v);
extern primitive_t * primitive_int64_new(primitive_t * o, int64 v);
extern primitive_t * primitive_uint8_new(primitive_t * o, uint8 v);
extern primitive_t * primitive_uint16_new(primitive_t * o, uint16 v);
extern primitive_t * primitive_uint32_new(primitive_t * o, uint32 v);
extern primitive_t * primitive_uint64_new(primitive_t * o, uint64 v);

extern int8 primitive_int8_get(primitive_t * o);
extern int16 primitive_int16_get(primitive_t * o);
extern int32 primitive_int32_get(primitive_t * o);
extern int64 primitive_int64_get(primitive_t * o);
extern uint8 primitive_uint8_get(primitive_t * o);
extern uint16 primitive_uint16_get(primitive_t * o);
extern uint32 primitive_uint32_get(primitive_t * o);
extern uint64 primitive_uint64_get(primitive_t * o);

extern primitive_t * primitive_string_new(primitive_t * o, const char * s);
extern primitive_t * primitive_string_del(primitive_t * o, uint32 flags);
extern const char * primitive_string_get(primitive_t * o);

#endif // __DISCOMPLEXITY__PRIMITIVE__H__
