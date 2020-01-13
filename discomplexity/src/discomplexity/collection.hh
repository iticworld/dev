#ifndef   __DISCOMPLEXITY__COLLECTION__HH__
#define   __DISCOMPLEXITY__COLLECTION__HH__

#include <discomplexity/container.hh>

namespace discomplexity
{
  template <typename T>
  class collection : public container
  {
  public:   collection(){}
  public:   virtual ~collection(){}
  
  public:   collection(const collection<T> & o) = delete;
  public:   collection(collection<T> && o) noexcept = delete;
  public:   collection<T> & operator=(const collection<T> & o) = delete;
  public:   collection<T> & operator=(collection<T> && o) noexcept = delete;
  };
}

#endif // __DISCOMPLEXITY__COLLECTION__HH__
