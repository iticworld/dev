#include <discomplexity/primitive.h>

#include <stdio.h>

int main()
{
  printf("sizeof(primitive_t) => %ld\n", sizeof(primitive_t));
  primitive_t o = PRIMITIVE_NULL;
  primitive_t * p = NULL;

  // ASSERT
  // printf("primitive_type is %s\n", primitive_type_string_get(NULL));
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 8 BIT INTEGER
  primitive_int8_new(&o, -14);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_int8_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 16 BIT INTEGER
  primitive_int16_new(&o, -3232);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_int16_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 32 BIT INTEGER
  primitive_int32_new(&o, -32322322);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_int32_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 64 BIT INTEGER
  primitive_int64_new(&o, 0xF00000012325L);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %lx\n", primitive_int64_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // printf("primitive value is %d\n", primitive_int8_get(&o));
  // printf("primitive type is %s\n", primitive_type_string_get(&p));

  // 8 BIT INTEGER
  primitive_uint8_new(&o, 14);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_uint8_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 16 BIT INTEGER
  primitive_uint16_new(&o, 3232);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_uint16_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 32 BIT INTEGER
  primitive_uint32_new(&o, 32322322);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %d\n", primitive_uint32_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));

  // 64 BIT INTEGER
  primitive_uint64_new(&o, 0x800000012325L);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  printf("primitive value is %lx\n", primitive_uint64_get(&o));
  primitive_del(&o, NONE);
  printf("primitive type is %s\n", primitive_type_string_get(&o));
  return 0;
}
