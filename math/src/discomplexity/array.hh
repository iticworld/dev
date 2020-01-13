#ifndef   __DISCOMPLEXITY__ARRAY__HH__
#define   __DISCOMPLEXITY__ARRAY__HH__

#include <discomplexity.hh>
#include <discomplexity/memory.hh>

#include <initializer_list>
#include <exception>

namespace discomplexity
{
  template <typename T>
  class array
  {
  protected:  T *     value_;
  protected:  uint64  length_;
  public:     inline bool empty() const { return this->value_ == nullptr || this->length_ == 0; }
  public:     inline uint64 size() const { return this->length_; }
  public:     inline const T & at(uint64 i) const
              {
                if(this->length_ <= i)
                {
                  throw std::exception();
                }
                if(this->value_ == nullptr)
                {
                  throw std::exception();
                }
                return this->value_[i];
              }
  public:     const T & operator[](uint64 i) const
              {
                if(this->length_ <= i)
                {
                  throw std::exception();
                }
                if(this->value_ == nullptr)
                {
                  throw std::exception();
                }
                return this->value_[i];
              }
  public:     T & operator[](uint64 i)
              {
                if(this->length_ <= i)
                {
                  throw std::exception();
                }
                if(this->value_ == nullptr)
                {
                  throw std::exception();
                }
                return this->value_[i];
              }
  public:     array<T> & operator=(const array<T> & o)
              {
                if(&o != this)
                {
                  this->value_  = memory::dup<T>(o.value_, o.length_);
                  this->length_ = o.length_;
                }
                return *this;
              }
  public:     array<T> & operator=(array<T> & o) noexcept
              {
                if(&o != this)
                {
                  this->value_  = o.value_;
                  this->length_ = o.length_;

                  o.value_  = nullptr;
                  o.length_ = 0;
                }
                return *this;
              }
  public:     array(const std::initializer_list<T> & list)
              {
                this->length_ = list.size();
                this->value_ = memory::gen<T>(this->length_);
                T * value = this->value_;
                for(typename std::initializer_list<T>::iterator it = list.begin(); it != list.end(); ++it, ++value)
                {
                  *value = *it;
                }
              }
  public:     array(uint64 len)
              {
                this->value_ = nullptr;
                this->length_ = len;
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
                if(&o != this)
                {
                  this->value_ = o.value_;
                  this->length_ = o.length_;

                  o.value_ = nullptr;
                  o.length_ = 0;
                }
              }
  public:     virtual ~array(void)
              {
                if(this->value_)
                {
                  this->value_ = memory::del<T>(this->value_);
                }
                this->length_ = 0;
              }
  };


}

#endif // __DISCOMPLEXITY__ARRAY__HH__
