#include "space.hh"

using namespace discomplexity;

int main()
{
  {
    space<int> o;
    std::cout << o << std::endl;
  }
  {
    space<int> o(1);
    std::cout << o << std::endl;
  }

  return 0;
}
