/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 4.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "novemberizing/core/memory.hh"

namespace novemberizing
{
    namespace core
    {

        void * memory::__allocate(uint64 n)
        {
            if(n > 0)
            {
                void * p = ::malloc(n);
                if(p == nullptr)
                {
                    ::printf("fail to ::malloc(...) caused by %d\n", errno);
                }
                return p;
            }
            return nullptr;
        }

        void * memory::__allocate(void * p, uint64 n)
        {
            if(n > 0)
            {
                if(p != nullptr)
                {
                    p = realloc(p, n);
                }
                else
                {
                    p = malloc(n);
                }
                return p;
            }
            else
            {
                if(p != nullptr)
                {
                    ::free(p);
                }
                return nullptr;
            }
        }

        void * memory::__deallocate(void * p)
        {
            if(p != nullptr)
            {
                ::free(p);
            }
            return nullptr;
        }

        void * memory::__copy(void * destination, const void * source, uint64 n)
        {
            if(destination != nullptr)
            {
                if(source != nullptr)
                {
                    ::memcpy(destination, source, n);
                }
                else
                {
                    if(n > 0)
                    {
                        printf("source == nullptr && n == 0\n");
                    }
                }
            }
            else
            {
                if(n > 0)
                {
                    printf("destination == nullptr && n > 0\n");
                }
            }
            return destination;
        }

        void * memory::__move(void * destination, const void * source, uint64 n)
        {
            if(destination != nullptr)
            {
                if(source != nullptr)
                {
                    ::memmove(destination, source, n);
                }
                else
                {
                    if(n > 0)
                    {
                        printf("source == nullptr && n == 0\n");
                    }
                }
            }
            else
            {
                if(n > 0)
                {
                    printf("destination == nullptr && n > 0\n");
                }
            }
            return destination;
        }

        void * memory::__fill(void * destination, int c, uint64 n)
        {
            if(destination != nullptr)
            {
                ::memset(destination, c, n);
            }
            else
            {
                if(n > 0)
                {
                    printf("destination == nullptr && n > 0\n");
                }
            }
            return destination;
        }

        memory::memory()
        {

        }

        memory::memory(const memory & o)
        {

        }

        memory::memory(memory && o) noexcept
        {

        }

        memory::~memory()
        {

        }

        memory & memory::operator=(const memory & o)
        {
            return *this;
        }

        memory & memory::operator=(memory && o) noexcept
        {
            return *this;
        }
    }
}

