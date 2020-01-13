#ifndef   __DISCOMPLEXITY__SPACE__HH__
#define   __DISCOMPLEXITY__SPACE__HH__

#include <discomplexity.hh>

#include <iostream>

namespace discomplexity
{
  /**
   * 상속 금지 클래스를 만들어야 한다.
   */
  template <typename T>
  class space
  {
  private:  destructor destructor_;
  private:  uint64 count_;
  private:  T value_;
  public:   const T & get() const { return this->value_; }
  public:   void set(const T & v){ this->value_ = v; }
  public:   void set(T && v){ this->value_ = std::move(v); }
  public:   inline uint64 count() const { return count_; }
  public:   inline void decrease(){ this->count_ = this->count_ - 1; }
  public:   inline void increase(){ this->count_ = this->count_ + 1; }
  public:   space<T> & operator=(const space<T> & o)
            {
              if(&o != this)
              {
                this->count_ = o.count_;
                this->value_ = o.value_;
              }
              return *this;
            }
  public:   space<T> & operator=(space<T> && o) noexcept
            {
              if(&o != this)
              {
                this->count_ = o.count_;
                this->value_ = std::move(o.value_);

                o.count_ = 0;
              }
              return *this;
            }
  public:   space(T && o) : destructor_(nullptr), count_(1), value_(std::move(o)) {}
  public:   space(const T & o) : destructor_(nullptr), count_(1), value_(o) {}
  public:   space(T && o, destructor f) : destructor_(f), count_(1), value_(std::move(o)) {}
  public:   space(const T & o, destructor f) : destructor_(f), count_(1), value_(o) {}
  public:   space() : destructor_(nullptr), count_(1), value_() {}
  public:   space(const space<T> & o) : destructor_(o.destructor_), count_(o.count_), value_(o.value_) {}
  public:   space(space<T> && o) noexcept : destructor_(o.destructor_), count_(o.count_), value_(std::move(o.value_))
            {
              o.destructor_ = nullptr;
              o.count_ = 0;
            }
  public:   ~space()
            {
              if(this->destructor_)
              {
                this->destructor_(value_);
              }
            }
  public:   friend std::ostream & operator<<(std::ostream & os, const space<T> & o)
            {
              os<<"{\"value\": "<< o.get() << ", \"count\": " << o.count() <<"}";
              return os;
            }
  };


}

#endif // __DISCOMPLEXITY__SPACE__HH__
