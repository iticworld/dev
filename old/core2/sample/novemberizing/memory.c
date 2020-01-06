#include <novemberizing.h>

int main(int argc, char ** argv)
{
    void * p = __novemberizing_core_memory_allocate(1024);
    p = __novemberizing_core_memory_reallocate(p, 4096);
    __novemberizing_core_memory_copy(p, "hello world", 11);
    __novemberizing_core_memory_move(p, &((char*)p)[5], 5);
    __novemberizing_core_memory_fill(&((char*)p)[5], 0, 5);
    __novemberizing_core_memory_deallocate(p);
    return 0;
}

