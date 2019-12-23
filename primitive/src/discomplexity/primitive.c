#include "primitive.h"

#include <assert.h>
#include <stdlib.h>

static primitive_t * primitive_int8_del(primitive_t * o, uint32 flags);

const char * primitive_type_string_get(const primitive_t * p)
{
  assert(p != NULL);

  switch(p->type)
  {
  case PRIMITIVE_TYPE_INT8:     return "int8";
  case PRIMITIVE_TYPE_INT16:    return "int16";
  case PRIMITIVE_TYPE_INT32:    return "int32";
  case PRIMITIVE_TYPE_INT64:    return "int64";
  case PRIMITIVE_TYPE_UINT8:    return "uint8";
  case PRIMITIVE_TYPE_UINT16:   return "uint16";
  case PRIMITIVE_TYPE_UINT32:   return "uint32";
  case PRIMITIVE_TYPE_UINT64:   return "uint64";
  }
  return "unknown";
}

primitive_t * primitive_del(primitive_t * o, uint32 flags)
{
  if(o)
  {
    switch(o->type)
    {
      case PRIMITIVE_TYPE_INT8: return primitive_int8_del(o, flags);
      default: assert(0);
    }
  }
  return o;
}

primitive_t * primitive_int8_new(primitive_t * o, int8 v)
{
  if(o == NULL)
  {
    o = malloc(sizeof(primitive_t));
    o->type = PRIMITIVE_TYPE_INT8;
  }
  else if(o->type == PRIMITIVE_TYPE_NONE)
  {
    o->type = PRIMITIVE_TYPE_INT8;
    assert(o->container == 0);
  }

  assert(o->type == PRIMITIVE_TYPE_INT8);

  o->container = v;

  return o;
}

static primitive_t * primitive_int8_del(primitive_t * o, uint32 flags)
{
  if(o)
  {
    o->type = PRIMITIVE_TYPE_NONE;
    o->container = 0;
    if(flags & DEALLOCATE)
    {
      free(o);
      o = NULL;
    }
  }
  return o;
}

int8 primitive_int8_get(primitive_t * o)
{
  assert(o != NULL);
  assert(o->type == PRIMITIVE_TYPE_INT8);

  return o->container;
}
