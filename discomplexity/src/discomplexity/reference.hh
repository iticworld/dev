#ifndef   __DISCOMPLEXITY__REFERENCE__HH__
#define   __DISCOMPLEXITY__REFERENCE__HH__

#include <discomplexity/space.hh>

namespace discomplexity
{
  /**
   * 상속금지
   */
  template <typename T>
  class reference
  {

  private:    space<T> * space_;
  public:     inline bool empty() const { return space_ == nullptr; }
  public:     inline void set(const T & v)
              {
                if(this->space_)
                {
                  this->space_->set(v);
                }
                else
                {
                  this->space_ = new T(v);
                }
              }
  public:     inline void set(T && v)
              {
                if(this->space_)
                {
                  this->space_->set(std::move(v));
                }
                else
                {
                  this->space_ = new T(std::move(v));
                }
              }
  public:     inline const T & get() const
              {
                if(this->space_ == nullptr)
                {
                  throw std::exception();
                }
                return this->space_->get();
              }
  public:     reference<T> & operator=(reference<T> && o) noexcept
              {
                if(&o != this)
                {
                  if(this->space_)
                  {
                    this->space_->decrease();
                    // std::cout<<"decrease"<<std::endl;
                    if(this->space_->count() <= 0)
                    {
                      // std::cout<<"delete"<<std::endl;
                      delete this->space_;
                    }
                  }
                  this->space_ = o.space_;
                }
                return *this;
              }
  public:     reference<T> & operator=(const reference<T> & o)
              {
                if(&o != this)
                {
                  if(this->space_)
                  {
                    this->space_->decrease();
                    // std::cout<<"decrease"<<std::endl;
                    if(this->space_->count() <= 0)
                    {
                      // std::cout<<"delete"<<std::endl;
                      delete this->space_;
                    }
                  }
                  this->space_ = o.space_;
                  if(this->space_)
                  {
                    this->space_->increase();
                  }
                }
                return *this;
              }
  public:     reference(const T & v) : space_(new space<T>(T(v))) {}
  public:     reference(T && v) : space_(new space<T>(T(std::move(v)))) {}
  public:     reference(const T & v, destructor f) : space_(new space<T>(T(v), f)) {}
  public:     reference(T && v, destructor f) : space_(new space<T>(T(std::move(v)), f)) {}
  public:     reference() : space_(nullptr) {}
  public:     reference(const reference<T> & o) : space_(o.space_)
              {
                if(this->space_)
                {
                  this->space_->increase();
                }
              }
  public:     reference(reference<T> && o) noexcept : space_(o.space_)
              {
                o.space_ = nullptr;
              }
  public:     ~reference()
              {
                if(this->space_)
                {
                  this->space_->decrease();
                  // std::cout<<"decrease"<<std::endl;
                  if(this->space_->count() <= 0)
                  {
                    // std::cout<<"delete"<<std::endl;
                    delete this->space_;
                  }
                  this->space_ = nullptr;
                }
              }
  public:     friend std::ostream & operator<<(std::ostream & os, const reference<T> & o)
              {
                os << "{\"space\":";
                if(o.space_)
                {
                  os << *(o.space_);
                }
                else
                {
                  os << "null";
                }
                os << "}";
                return os;
              }
  };
}

#endif // __DISCOMPLEXITY__REFERENCE__HH__
