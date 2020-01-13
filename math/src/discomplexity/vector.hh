#ifndef   __DISCOMPLEXITY__VECTOR__HH__
#define   __DISCOMPLEXITY__VECTOR__HH__

#include <discomplexity/array.hh>

namespace discomplexity
{
  template <typename T>
  class vector
  {
  protected:  array<T> container_;
  public:     uint64 size() const { return container_.size(); }
  public:     const T & at(uint64 i) const { return container_.at(i); }
  public:     const T & operator[](uint64 i) const { return container_[i]; }
  public:     T & operator[](uint64 i) { return container_[i]; }
  public:     vector<T> & operator=(const vector<T> & o)
              {
                if(&o != this)
                {
                  this->container_ = o.container_;
                }
                return *this;
              }
  public:     vector<T> & operator=(vector<T> && o) noexcept
              {
                if(&o != this)
                {
                  this->container_ = std::move(o.container_);
                }
                return *this;
              }
  public:     vector(std::initializer_list<T> list) : container_(list) {}
  public:     vector() : container_() {}
  public:     vector(vector<T> && o) noexcept : container_(o.container_) {}
  public:     vector(const vector<T> & o) : container_(std::move(o.container_)) {}
  public:     virtual ~vector() {}
  };
}

#endif // __DISCOMPLEXITY__VECTOR__HH__
