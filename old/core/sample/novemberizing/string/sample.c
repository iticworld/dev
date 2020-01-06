#include <novemberizing.h>

#include <stdio.h>

int main(int argc, char ** argv)
{
    printf("%ld\n", __novemberizing_string_length("hello world"));
    printf("%d\n", __novemberizing_string_compare("hello", "world", 5));
    return 0;
}
