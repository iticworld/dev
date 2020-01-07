POLYGON
=======

```c++
#include <opencv2/imgproc.hpp>

void cv::fillPoly(InputOutputArray image,
                  const Point **   points,
                  const Point *    n,
                  int              ncontours,
                  const Scalar &   color,
                  int              type = LINE_8,
                  int              shift = 0,
                  Point            offset = Point())
```

This is an overloaded member function, provide for convenience.
It differs from the above function in what argument it accepts.
