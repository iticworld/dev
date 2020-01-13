#include "point.hh"

#include <iostream>

int main()
{
  point<int> a = { -1, 2 };
  point<int> b = {  3, 4 };
  std::cout << a <<std::endl;
  return 0;
}
