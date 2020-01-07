/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__CORE__MEMORY__HH__
#define   __NOVEMBERIZING__CORE__MEMORY__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    namespace core
    {
        class memory
        {
        protected:  static void * __allocate(uint64 n);
        protected:  static void * __allocate(void * p, uint64 n);
        protected:  static void * __deallocate(void * p);
        protected:  static void * __copy(void * destination, const void * source, uint64 n);
        protected:  static void * __move(void * destination, const void * source, uint64 n);
        protected:  static void * __fill(void * destination, int c, uint64 n);
        public:     template <typename T> static T * allocate(uint64 n);
        public:     template <typename T> static T * allocate(T * p, uint64 n);
        public:     template <typename T> static T * deallocate(T * p);
        public:     template <typename T> static T * copy(T * destination, const T * source, uint64 n);
        public:     template <typename T> static T * move(T * destination, const T * source, uint64 n);
        public:     template <typename T> static T * fill(T * destination, const T & o, uint64 n);
        public:     template <typename T> static T * fill(T * destination, T && o, uint64 n);
        public:     memory & operator=(const memory & o);
        public:     memory & operator=(memory && o) noexcept;
        public:     memory();
        public:     memory(const memory & o);
        public:     memory(memory && o) noexcept;
        public:     virtual ~memory();
        };
    }
}

#include <novemberizing/core/memory.hp>

#endif // __NOVEMBERIZING__CORE__MEMORY__HH__
