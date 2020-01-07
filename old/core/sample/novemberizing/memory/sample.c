#include <novemberizing.h>

#include <stdio.h>

int main(int argc, char ** argv)
{
    void * p = __novemberizing_memory_allocate(1024);
    __novemberizing_memory_fill(p, 0, 256);
    __novemberizing_memory_copy(&p[256], "hello", 5);
    __novemberizing_memory_move(p, &p[256], 5);
    __novemberizing_memory_reallocate(p, 256);
    printf("%s\n", (char *) p);
    __novemberizing_memory_deallocate(p);
    return 0;
}

