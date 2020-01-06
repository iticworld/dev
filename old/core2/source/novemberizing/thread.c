/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 26.
 */

#include "novemberizing.h"

#ifndef    WIN32
#include <pthread.h>
_handle __novemberizing_core_thread_new()
{

}
_int32 __novemberizing_core_thread_start(_handle h, __novemberizing_core_thread_routine f, void * param)
{
    return 0;
}
_int32 __novemberizing_core_thread_stop(_handle h)
{
    return 0;
}
_handle __novemberizing_core_thread_free(_handle h)
{
    return 0;
}
#else   // WIN32
#include <windows.h>

static DWORD WINAPI __novemberizing_core_thread_routine_external(void * param);

struct __novemberizing_core_thread
{
    HANDLE handle;
    DWORD id;
    __novemberizing_core_thread_routine routine;
    void * param;
};

static DWORD WINAPI __novemberizing_core_thread_routine_external(void * param)
{
    struct __novemberizing_core_thread * t = (struct __novemberizing_core_thread *) param;
    if(t != NULL)
    {
        if(t->routine)
        {
            t->routine(t->param);
        }
        t->routine = NULL;
        t->param = NULL;
    }
    return (DWORD)(-1);
}

_handle __novemberizing_core_thread_new()
{
    struct __novemberizing_core_thread * t = calloc(sizeof(struct __novemberizing_core_thread), 1);
    return t;
}

_handle __novemberizing_core_thread_free(_handle h)
{
    struct __novemberizing_core_thread * t = (struct __novemberizing_core_thread *) h;
    if(t != NULL)
    {
        if(t->handle)
        {
            while(t->routine)
            {
                Sleep(1);
            }
            t->handle = 0;
            t->id = 0;
        }
        free(t);
    }
    return NULL;
}

_int32 __novemberizing_core_thread_start(_handle h, __novemberizing_core_thread_routine f, void * param)
{
    struct __novemberizing_core_thread * t = (struct __novemberizing_core_thread *) h;
    if(t != NULL)
    {
        if(t->handle == NULL)
        {
            t->routine = f;
            t->param = param;
            t->handle = CreateThread(NULL, 0, __novemberizing_core_thread_routine_external, t, 0, &t->id);
            if(t->handle)
            {
                return 0;
            }
            /** error handling */
        }
    }
    return -1;
}

_int32 __novemberizing_core_thread_stop(_handle h)
{
    struct __novemberizing_core_thread * t = (struct __novemberizing_core_thread *) h;
    if(t != NULL)
    {
        if(t->handle)
        {
            while(t->routine)
            {
                Sleep(1);
            }
            t->handle = 0;
            t->id = 0;
        }
        return 0;
    }
    return -1;
}

#endif  // WIN32


