/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__MEMORY__HH__
#define   __NOVEMBERIZING__MEMORY__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    namespace memory
    {
        template <typename T>
        T * allocate(type::size n)
        {
            return static_cast<T *>(__novemberizing_memory_allocate(sizeof(T) * n));
        }

        template <>
        void * allocate<void>(type::size n)
        {
            return __novemberizing_memory_allocate(n);
        }

        template <typename T>
        T * allocate(T * original, type::size n)
        {
            return static_cast<T *>(__novemberizing_memory_reallocate(original, sizeof(T) * n));
        }

        template <>
        void * allocate<void>(void * original, type::size n)
        {
            return __novemberizing_memory_reallocate(original, n);
        }

        template <typename T>
        T * deallocate(T * p)
        {
            __novemberizing_memory_deallocate(p);
            return nullptr;
        }

        template <typename T>
        T * copy(T * destination, const T * source, type::size n)
        {
            if(destination != nullptr && source!=nullptr && n > 0)
            {
                for(type::size i = 0; i < n; i++)
                {
                    destination[i] = source[i];
                }
            }
            return destination;
        }

        template <>
        void * copy<void>(void * destination, const void * source, type::size n)
        {
            return __novemberizing_memory_copy(destination, source, n);
        }

        template <>
        char * copy<char>(char * destination, const char * source, type::size n)
        {
            return static_cast<char *>(__novemberizing_memory_copy(destination, source, sizeof(char) * n));
        }

        template <>
        signed char * copy<signed char>(signed char * destination, const signed char * source, type::size n)
        {
            return static_cast<signed char *>(__novemberizing_memory_copy(destination, source, sizeof(signed char) * n));
        }

        template <>
        unsigned char * copy<unsigned char>(unsigned char * destination, const unsigned char * source, type::size n)
        {
            return static_cast<unsigned char *>(__novemberizing_memory_copy(destination, source, sizeof(unsigned char) * n));
        }

        template <>
        short * copy<short>(short * destination, const short * source, type::size n)
        {
            return static_cast<short *>(__novemberizing_memory_copy(destination, source, sizeof(short) * n));
        }

        template <>
        unsigned short * copy<unsigned short>(unsigned short * destination, const unsigned short * source, type::size n)
        {
            return static_cast<unsigned short *>(__novemberizing_memory_copy(destination, source, sizeof(unsigned short) * n));
        }

        template <>
        int * copy<int>(int * destination, const int * source, type::size n)
        {
            return static_cast<int *>(__novemberizing_memory_copy(destination, source, sizeof(int) * n));
        }

        template <>
        unsigned int * copy<unsigned int>(unsigned int * destination, const unsigned int * source, type::size n)
        {
            return static_cast<unsigned int *>(__novemberizing_memory_copy(destination, source, sizeof(unsigned int) * n));
        }

        template <>
        long * copy<long>(long * destination, const long * source, type::size n)
        {
            return static_cast<long *>(__novemberizing_memory_copy(destination, source, sizeof(long) * n));
        }

        template <>
        unsigned long * copy<unsigned long>(unsigned long * destination, const unsigned long * source, type::size n)
        {
            return static_cast<unsigned long *>(__novemberizing_memory_copy(destination, source, sizeof(unsigned long) * n));
        }

        template <>
        long long * copy<long long>(long long * destination, const long long * source, type::size n)
        {
            return static_cast<long long *>(__novemberizing_memory_copy(destination, source, sizeof(long long) * n));
        }

        template <>
        unsigned long long * copy<unsigned long long>(unsigned long long * destination, const unsigned long long * source, type::size n)
        {
            return static_cast<unsigned long long *>(__novemberizing_memory_copy(destination, source, sizeof(unsigned long long) * n));
        }

        template <typename T>
        T * move(T * destination, const T * source, type::size n)
        {
            return static_cast<T *>(__novemberizing_memory_move(destination, source, n));
        }

        template <>
        void * move(void * destination, const void * source, type::size n)
        {
            return __novemberizing_memory_move(destination, source, n);
        }

        void * set(void * destination, int c, type::size n)
        {
            return __novemberizing_memory_fill(destination, c, n);
        }

        template <typename T>
        T * fill(T * destination, const T & source, type::size n)
        {
            if(destination != nullptr && n > 0)
            {
                for(type::size i = 0; i < n; i++)
                {
                    destination[i] = source;
                }
            }
            return destination;
        }

        template <>
        char * fill(char * destination, const char & source, type::size n)
        {
            return static_cast<char *>(__novemberizing_memory_fill(destination, source, n));
        }

        template <>
        signed char * fill(signed char * destination, const signed char & source, type::size n)
        {
            return static_cast<signed char *>(__novemberizing_memory_fill(destination, source, n));
        }

        template <>
        unsigned char * fill(unsigned char * destination, const unsigned char & source, type::size n)
        {
            return static_cast<unsigned char *>(__novemberizing_memory_fill(destination, source, n));
        }
    }
}

#endif // __NOVEMBERIZING__MEMORY__HH__
