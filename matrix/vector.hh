#ifndef   __DISCOMPLEXITY__VECTOR__HH__
#define   __DISCOMPLEXITY__VECTOR__HH__

namespace discomplexity
{
  template <typename T>
  class vector
  {
  public: vector();
  public: vector(const vector<T> & o);
  public: vector(vector<T> && o);
  public: virtual ~vector();
  };
}

#endif // __DISCOMPLEXITY__VECTOR__HH__
