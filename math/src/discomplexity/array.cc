#include "array.hh"

#include <string>

using namespace discomplexity;

int main()
{
  {
  }
  {
    array<int> o;
    for(int i = 0; i < o.size(); i++)
    {
      printf("%d\n", o.at(i));
    }
  }
  {
    array<int> o({ 2, 4});
    for(int i = 0; i < o.size(); i++)
    {
      printf("%d\n", o.at(i));
    }
    printf("%d\n", o[0]);
    {
      array<int> destination = o;
      for(int i = 0; i < destination.size(); i++)
      {
        printf("%d\n", destination.at(i));
      }
    }

    {
      array<int> destination = std::move(o);
      for(int i = 0; i < destination.size(); i++)
      {
        printf("%d\n", destination.at(i));
      }
    }
  }

  // array<int> o({ 2, 4});
  return 0;
}
