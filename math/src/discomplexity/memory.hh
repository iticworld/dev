#ifndef   __DISCOMPLEXITY__MEMORY__HH__
#define   __DISCOMPLEXITY__MEMORY__HH__

#include <discomplexity.hh>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <exception>

namespace discomplexity
{
  namespace memory
  {
    template <typename T>
    inline T * gen(uint64 len)
    {
      return (T *)(::malloc(len * sizeof(T)));
    }

    template <> inline int8   * gen(uint64 len){ return (int8   *)(::calloc(sizeof(int8  ), len)); }
    template <> inline int16  * gen(uint64 len){ return (int16  *)(::calloc(sizeof(int16 ), len)); }
    template <> inline int32  * gen(uint64 len){ return (int32  *)(::calloc(sizeof(int32 ), len)); }
    template <> inline int64  * gen(uint64 len){ return (int64  *)(::calloc(sizeof(int64 ), len)); }
    template <> inline uint8  * gen(uint64 len){ return (uint8  *)(::calloc(sizeof(uint8 ), len)); }
    template <> inline uint16 * gen(uint64 len){ return (uint16 *)(::calloc(sizeof(uint16), len)); }
    template <> inline uint32 * gen(uint64 len){ return (uint32 *)(::calloc(sizeof(uint32), len)); }
    template <> inline uint64 * gen(uint64 len){ return (uint64 *)(::calloc(sizeof(uint64), len)); }

    template <typename T>
    inline T * dup(const T * p, uint64 len)
    {
      // IMPLEMENT THIS
      THROW();
    }

    template <> inline int8   * dup(const int8 * p, uint64 len)
    {
      int8 * out = (int8 *) ::calloc(sizeof(int8), len);
      memcpy(out, p, len * sizeof(int8));
      return out;
    }
    template <> inline int16  * dup(const int16 * p, uint64 len)
    {
      int16 * out = (int16 *) ::calloc(sizeof(int16), len);
      memcpy(out, p, len * sizeof(int16));
      return out;
    }
    template <> inline int32  * dup(const int32 * p, uint64 len)
    {
      int32 * out = (int32 *) ::calloc(sizeof(int32), len);
      memcpy(out, p, len * sizeof(int32));
      return out;
    }
    template <> inline int64  * dup(const int64 * p, uint64 len)
    {
      int64 * out = (int64 *) ::calloc(sizeof(int64), len);
      memcpy(out, p, len * sizeof(int64));
      return out;
    }
    template <> inline uint8  * dup(const uint8 * p, uint64 len)
    {
      uint8 * out = (uint8 *) ::calloc(sizeof(uint8), len);
      memcpy(out, p, len * sizeof(uint8));
      return out;
    }
    template <> inline uint16 * dup(const uint16 * p, uint64 len)
    {
      uint16 * out = (uint16 *) ::calloc(sizeof(uint16), len);
      memcpy(out, p, len * sizeof(uint16));
      return out;
    }
    template <> inline uint32 * dup(const uint32 * p, uint64 len)
    {
      uint32 * out = (uint32 *) ::calloc(sizeof(uint32), len);
      memcpy(out, p, len * sizeof(uint32));
      return out;
    }
    template <> inline uint64 * dup(const uint64 * p, uint64 len)
    {
      uint64 * out = (uint64 *) ::calloc(sizeof(uint64), len);
      memcpy(out, p, len * sizeof(uint64));
      return out;
    }

    template <typename T>
    inline T * del(T * p)
    {
      if(p)
      {
        ::free(p);
      }
      return nullptr;
    }


  }
}

#endif // __DISCOMPLEXITY__MEMORY__HH__
