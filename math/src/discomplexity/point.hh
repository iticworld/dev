#ifndef   __DISCOMPLEXITY__POINT__HH__
#define   __DISCOMPLEXITY__POINT__HH__

#include <discomplexity/array.hh>

namespace discomplexity
{
  template <typename T>
  class point
  {
  protected:  array<T> container_;
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
  public:     point(point<T> && o) noexcept : container_(o.container_) {}
  public:     point(const point<T> & o) : container_(std::move(o.container_)) {}
  public:     virtual ~point() {}
  };
}

#endif // __DISCOMPLEXITY__POINT__HH__
