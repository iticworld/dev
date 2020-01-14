#ifndef   __DISCOMPLEXITY__VECTOR__HH__
#define   __DISCOMPLEXITY__VECTOR__HH__

#include <discomplexity.hh>
#include <discomplexity/memory.hh>

namespace discomplexity
{
  template <typename T>
  class vector
  {
  protected:  T *     value_;
  protected:  uint64  size_;
  public:     vector<T> & operator=(const vector<T> & o);
  public:     vector<T> & operator=(vector<T> && o) noexcept;
  public:     vector();
  public:     vector(const vector<T> & o);
  public:     vector(vector<T> && o) noexcept;
  public:     virtual ~vector()
              {
                if(this->value_)
                {
                  this->value_ = memory::del<T>(this->value_);
                }
                this->size_ = 0;
              }
  };
}

#endif // __DISCOMPLEXITY__VECTOR__HH__
