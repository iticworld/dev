#include "point.hh"
#include "vector.hh"


#include <iostream>

using namespace discomplexity;

int main()
{
  point<int> a = { -1, 2 };
  point<int> b = {  3, 4 };
  printf("%d, %d\n", b[0], b[1]);
  // std::cout << a <<std::endl;
  vector<int> v = b - a;
  for(int i = 0; i < v.size(); i++)
  {
    printf("%d\n", v[i]);
  }

  vector<int> x = { 3, -1 };
  vector<int> y = { 1,  4 };
  vector<int> result = x + y;
  printf("[ %d, %d]\n", result[0], result[1]);
  return 0;
}
