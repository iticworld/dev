#ifndef   __DISCOMPLEXITY__CONTAINER__HH__
#define   __DISCOMPLEXITY__CONTAINER__HH__

#include <discomplexity.hh>

namespace discomplexity
{
  class container
  {
  public:   virtual bool empty() const = 0;
  public:   virtual uint64 size() const = 0;
  public:   container() {}
  public:   virtual ~container() {}
  public:   container(const container & o) = delete;
  public:   container(container && o) noexcept = delete;
  public:   container & operator=(const container & o) = delete;
  public:   container & operator=(container && o) noexcept = delete;
  };
}

#endif // __DISCOMPLEXITY__CONTAINER__HH__
