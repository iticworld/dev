#ifndef   __DISCOMPLEXITY__VECTOR__HH__
#define   __DISCOMPLEXITY__VECTOR__HH__

#include <discomplexity/array.hh>
#include <discomplexity/point.hh>

namespace discomplexity
{
  template <typename T>
  class vector
  {
  public:     static vector<T> gen(const point<T> a, const point<T> b)
              {
                // return b - a;
              }
  protected:  array<T> container_;
  public:     const array<T> & container() const { return this->container_; }
  public:     array<T> & container() { return this->container_; }
  public:     bool empty() const { return container_.empty(); }
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
  public:     vector(const point<T> & o) : container_(o.container()) {}
  public:     vector(std::initializer_list<T> list) : container_(list) {}
  public:     vector() : container_() {}
  public:     vector(vector<T> && o) noexcept : container_(std::move(o.container_)) {}
  public:     vector(const vector<T> & o) : container_(o.container_) {}
  public:     virtual ~vector() {}
  };

  template <typename C, typename T> vector<T> operator*(C c, const vector<T> & x)
  {
    if(x.empty())
    {
      throw std::exception();
    }
    vector<T> out = x;
    for(uint64 i = 0; i < out.size(); i++)
    {
      out[i] *= c;
    }
    return out;
  }

  template <typename T> vector<T> operator+(const vector<T> & x, const vector<T> & y)
  {
    if(x.size() != y.size())
    {
      throw std::exception();
    }
    if(x.empty() || y.empty())
    {
      throw std::exception();
    }
    vector<T> out = x;
    for(uint64 i = 0; i < out.size(); i++)
    {
      out[i] += y[i];
    }
    return out;
  }
}

#endif // __DISCOMPLEXITY__VECTOR__HH__
