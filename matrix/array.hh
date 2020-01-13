#ifndef   __DISCOMPLEXITY__ARRAY__HH__
#define   __DISCOMPLEXITY__ARRAY__HH__

namespace discomplexity
{
  template <typename T>
  class array
  {
  protected:  T *     value_;
  protected:  uint64  length_;
  public:     array<T> & operator=(const array<T> & o)
              {
                return *this;
              }
  public:     array<T> & operator=(array<T> & o) noexcept
              {
                  return *this;
              }
  public:     array()
              {
                this->value_  = nullptr;
                this->length_ = 0;
              }
  public:     array(const array<T> & o)
              {
                if(&o != this)
                {
                  this->value_  = memory::dup<T>(o.value_, o.length_);
                  this->length_ = o.length_;
                }
              }
  public:     array(array<T> && o) noexcept
              {

              }
  public:     virtual ~array(void)
              {

              }
  };
}

#endif // __DISCOMPLEXITY__ARRAY__HH__
