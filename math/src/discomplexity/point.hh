#ifndef   __DISCOMPLEXITY__POINT__HH__
#define   __DISCOMPLEXITY__POINT__HH__

#include <discomplexity/array.hh>

namespace discomplexity
{
  template <typename T>
  class point
  {
  protected:  array<T> container_;
  public:     const array<T> & container() const { return this->container_; }
  public:     array<T> & container() { return this->container_; }
  public:     bool empty() const { return container_.empty(); }
  public:     uint64 size() const { return container_.size(); }
  public:     const T & at(uint64 i) const { return container_.at(i); }
  public:     const T & operator[](uint64 i) const { return container_[i]; }
  public:     T & operator[](uint64 i) { return container_[i]; }
  public:     point<T> & operator=(const point<T> & o)
              {
                if(&o != this)
                {
                  this->container_ = o.container_;
                }
                return *this;
              }
  public:     point<T> & operator=(point<T> && o) noexcept
              {
                if(&o != this)
                {
                  this->container_ = std::move(o.container_);
                }
                return *this;
              }
  public:     point(std::initializer_list<T> list) : container_(list) {}
  public:     point() : container_() {}
  public:     point(point<T> && o) noexcept : container_(std::move(o.container_)) {}
  public:     point(const point<T> & o) : container_(o.container_) {}
  public:     virtual ~point() {}
  };

  template <typename T> point<T> operator-(const point<T> & x, const point<T> & y)
  {
    if(x.size() != y.size())
    {
      throw std::exception();
    }
    if(x.empty() || y.empty())
    {
      throw std::exception();
    }
    point<T> out = x;
    for(uint64 i = 0; i < out.size(); i++)
    {
      out[i] -= y[i];
    }
    return out;
  }
}

#endif // __DISCOMPLEXITY__POINT__HH__
