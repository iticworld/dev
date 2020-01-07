#include <novemberizing.h>

#include <stdio.h>

static void * thread_routine_sample(void * param)
{
    for(int i = 0; i < 5; i++)
    {
        printf("thread is running: %p\n", param);
    }

    return NULL;
}

int main(int argc, char ** argv)
{
    _handle h = __novemberizing_core_thread_new();
    printf("%p\n", h);
    __novemberizing_core_thread_start(h, thread_routine_sample, NULL);
    h = __novemberizing_core_thread_free(h);
    printf("%p\n", h);

    h = __novemberizing_core_thread_new();
    printf("%p\n", h);
    __novemberizing_core_thread_start(h, thread_routine_sample, NULL);
    __novemberizing_core_thread_stop(h);
    h = __novemberizing_core_thread_free(h);
    printf("%p\n", h);

    return 0;
}

