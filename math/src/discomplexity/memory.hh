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

    template <> inline int8   * gen(uint64 len){ DEBUG_(); return (int8   *)(::calloc(sizeof(int8  ), len)); }
    template <> inline int16  * gen(uint64 len){ DEBUG_(); return (int16  *)(::calloc(sizeof(int16 ), len)); }
    template <> inline int32  * gen(uint64 len){ DEBUG_(); return (int32  *)(::calloc(sizeof(int32 ), len)); }
    template <> inline int64  * gen(uint64 len){ DEBUG_(); return (int64  *)(::calloc(sizeof(int64 ), len)); }
    template <> inline uint8  * gen(uint64 len){ DEBUG_(); return (uint8  *)(::calloc(sizeof(uint8 ), len)); }
    template <> inline uint16 * gen(uint64 len){ DEBUG_(); return (uint16 *)(::calloc(sizeof(uint16), len)); }
    template <> inline uint32 * gen(uint64 len){ DEBUG_(); return (uint32 *)(::calloc(sizeof(uint32), len)); }
    template <> inline uint64 * gen(uint64 len){ DEBUG_(); return (uint64 *)(::calloc(sizeof(uint64), len)); }

    template <typename T>
    inline T * dup(const T * p, uint64 len)
    {
      // IMPLEMENT THIS
      throw std::exception();
    }

    template <> inline int8   * dup(const int8 * p, uint64 len)
    {
      DEBUG_();
      int8 * out = (int8 *) ::calloc(sizeof(int8), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline int16  * dup(const int16 * p, uint64 len)
    {
      DEBUG_();
      int16 * out = (int16 *) ::calloc(sizeof(int16), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline int32  * dup(const int32 * p, uint64 len)
    {
      DEBUG_();
      int32 * out = (int32 *) ::calloc(sizeof(int32), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline int64  * dup(const int64 * p, uint64 len)
    {
      DEBUG_();
      int64 * out = (int64 *) ::calloc(sizeof(int64), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline uint8  * dup(const uint8 * p, uint64 len)
    {
      DEBUG_();
      uint8 * out = (uint8 *) ::calloc(sizeof(uint8), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline uint16 * dup(const uint16 * p, uint64 len)
    {
      DEBUG_();
      uint16 * out = (uint16 *) ::calloc(sizeof(uint16), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline uint32 * dup(const uint32 * p, uint64 len)
    {
      DEBUG_();
      uint32 * out = (uint32 *) ::calloc(sizeof(uint32), len);
      memcpy(out, p, len);
      return out;
    }
    template <> inline uint64 * dup(const uint64 * p, uint64 len)
    {
      DEBUG_();
      uint64 * out = (uint64 *) ::calloc(sizeof(uint64), len);
      memcpy(out, p, len);
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
