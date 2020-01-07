#include <novemberizing.h>

#include <stdio.h>

int main(int argc, char ** argv)
{
    const char * x = "hello";
    const char * y = "world";
#ifdef    WIN32
    printf("length: %d\n", __novemberizing_core_string_length(x));
#else  // WIN32
    printf("length: %ld\n", __novemberizing_core_string_length(x));
#endif // WIN32
    printf("compare: %d\n", __novemberizing_core_string_compare(x, y, 5));
    char * s = __novemberizing_core_string_new("hello world");
    printf("%s\n", s);
    s = __novemberizing_core_string_reset(s, "hello novemberizing");
    printf("%s\n", s);
    return 0;
}

