#include "reference.hh"

using namespace discomplexity;

int main()
{
  {
    reference<int> o;
    std::cout<<o<<std::endl;
  }
  {
    reference<int> o(1);
    std::cout<<o<<std::endl;
  }
  {
    reference<int> x(1);
    reference<int> y[16];
    for(int i = 0; i < 16; i++)
    {
      y[i] = x;
      std::cout<<y[i]<<std::endl;
    }
  }
  return 0;
}
