#ifndef   __DISCOMPLEXITY__ARRAY__HH__
#define   __DISCOMPLEXITY__ARRAY__HH__

#include <discomplexity/collection.hh>
#include <discomplexity/reference.hh>
#include <discomplexity/memory.hh>

namespace discomplexity
{
  template <typename T>
  class array : public collection<T>
  {
  protected:  T * container_;
  protected:  uint64 size_;
  public:     bool empty() const override { return this->container_ == nullptr || this->size_ == 0; };
  public:     uint64 size() const override { return this->size_; }
  public:     array<T> & operator=(array<T> && o) noexcept
              {
                if(&o != this)
                {
                  if(this->container_)
                  {
                    this->container_ = memory::del<T>(this->container_);
                  }
                  this->container_ = o.container_;
                  this->size_ = o.size_;

                  o.container_ = nullptr;
                  o.size_ = 0;
                }
                return *this;
              }
  public:     array<T> & operator=(const array<T> & o)
              {
                if(&o != this)
                {
                  if(this->container_)
                  {
                    this->container_ = memory::del<T>(this->container_);
                  }
                  this->container_ = memory::gen<T>(o.size_);
                  this->size_ = o.size_;
                  for(uint64 i = 0; i < this->size_; i++)
                  {
                    this->container_[i] = o.container_[i];
                  }
                }
                return *this;
              }
  public:     array() : container_(nullptr), size_(0) {}
  public:     array(array<T> && o) noexcept : container_(o.container_), size_(o.size_)
              {
                o.container_ = nullptr;
                o.size_ = 0;
              }
  public:     array(const array<T> & o) : container_(memory::gen<T>(o.size())), size_(o.size())
              {
                for(uint64 i = 0; i < o.size(); i++)
                {
                  this->container_[i] = o.container_[i];
                }
              }
  public:     array(const std::initializer_list<T> & list) : container_(memory::gen<T>(list.size())), size_(list.size())
              {
                T * p = this->container_;
                if(p)
                {
                  for(typename std::initializer_list<T>::iterator it = list.begin(); it != list.end(); ++it, ++p)
                  {
                    *p = *it;
                  }
                }
              }
  public:     virtual ~array()
              {
                if(this->container_)
                {
                  this->container_ = memory::del<T>(this->container_);
                }
                this->size_ = 0;
              }
  public:     friend std::ostream & operator<<(std::ostream & os, const array<T> & o)
              {
                if(o.container_)
                {
                  os << "[";
                  for(uint64 i = 0; i < o.size_; i++)
                  {
                    os << o.container_[i] << (i + 1 != o.size_ ? "," : "");
                  }
                  os << "]";
                }
                else
                {
                  os << "null";
                }
                return os;
              }
  };
}

#endif // __DISCOMPLEXITY__ARRAY__HH__
