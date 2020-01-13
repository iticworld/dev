#ifndef   __DISCOMPLEXITY__HH__
#define   __DISCOMPLEXITY__HH__

#include <iostream>
#include <exception>

namespace discomplexity
{
  typedef __INT8_TYPE__    int8;
  typedef __INT16_TYPE__  int16;
  typedef __INT32_TYPE__  int32;
  typedef __INT64_TYPE__  int64;
  typedef __UINT8_TYPE__  uint8;
  typedef __UINT16_TYPE__ uint16;
  typedef __UINT32_TYPE__ uint32;
  typedef __UINT64_TYPE__ uint64;

  extern const char * version();

  typedef void (*destructor)(void *);

  // std::ostream & operator<<(std::ostream & os, int64 o)
  // {
  //   os<<(long) o;
  //   return os;
  // }
  // std::ostream & operator<<(std::ostream & os, uint64 o)
  // {
  //   os<<(unsigned long) o;
  //   return os;
  // }
}

#endif // __DISCOMPLEXITY__HH__
