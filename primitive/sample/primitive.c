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
  // printf("primitive value is %d\n", primitive_int8_get(&o));
  // printf("primitive type is %s\n", primitive_type_string_get(&p));
  return 0;
}
