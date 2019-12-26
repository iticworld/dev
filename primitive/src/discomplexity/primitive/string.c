#include "../primitive.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct __primitive_string_container_t
{
  uint64 capacity;
  uint64 length;
  char * v;
};

typedef struct __primitive_string_container_t primitive_string_container_t;

static const uint64 page = 64;

static container_t primitive_string_container_new(container_t c, const char * s);
static container_t primitive_string_container_del(container_t c);
static const char * primitive_string_container_get(container_t c);

primitive_t * primitive_string_new(primitive_t * o, const char * s)
{
  if(o == NULL)
  {
    o = malloc(sizeof(primitive_t));
    o->type = PRIMITIVE_TYPE_STRING;
  }
  else if(o->type == PRIMITIVE_TYPE_NONE)
  {
    o->type = PRIMITIVE_TYPE_STRING;
    assert(o->container == 0);
  }
  assert(o->type == PRIMITIVE_TYPE_STRING);
  o->container = primitive_string_container_new(o->container, s);
  return o;
}

static container_t primitive_string_container_new(container_t c, const char * s)
{
  primitive_string_container_t * container = c ? (primitive_string_container_t *)(c) : calloc(sizeof(primitive_string_container_t), 1);

  uint64 length = s ? strlen(s) : 0;
  uint64 capacity = ((length + 1) / page + 1) * page;
  // adjust capacity
  if(container->capacity < capacity)
  {
    if(container->v)
    {
      container->v = realloc(container->v, capacity);
    }
    else
    {
      container->v = malloc(capacity);
    }
    container->capacity = capacity;
  }
  container->length = length;
  if(length > 0)
  {
    memcpy(container->v, s, length);
  }
  container->v[length] = 0;

  return (container_t)(container);
}

static container_t primitive_string_container_del(container_t c)
{
  primitive_string_container_t * container = (primitive_string_container_t *)(c);
  if(container)
  {
    if(container->v)
    {
      free(container->v);
    }
    free(container);
    container = NULL;
  }
  return (container_t)(container);
}

primitive_t * primitive_string_del(primitive_t * o, uint32 flags)
{
  if(o)
  {
    o->type = PRIMITIVE_TYPE_NONE;
    o->container = primitive_string_container_del(o->container);
    if(flags & DEALLOCATE)
    {
      free(o);
      o = NULL;
    }
  }
  return o;
}

const char * primitive_string_get(primitive_t * o)
{
  assert(o != NULL);
  assert(o->type == PRIMITIVE_TYPE_STRING);

  return primitive_string_container_get(o->container);
}

static const char * primitive_string_container_get(container_t c)
{
  primitive_string_container_t * container = (primitive_string_container_t *) c;
  return container ? container->v : NULL;
}
