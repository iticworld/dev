#include "array.hh"

using namespace discomplexity;

int main()
{
  {
    array<int> o;
  }
  {
    array<int> o = {1, 2, 3, 4, 5};
    std::cout << o << std::endl;
  }

  return 0;
}
