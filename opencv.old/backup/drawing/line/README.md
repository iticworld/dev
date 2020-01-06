LINE
====

```c++
#include <opencv2/imgproc.hpp>

void cv::line(InputOutputArray image,
              Point            start,
              Point            end,
              const Scalar &   color,
              int              thickness = 1,
              int              type = LINE_8,
              int              shift = 0)
```

Draws a line segment connecting two points.

The function line draws the line segment between start and end points in the image.
The line is clipped by the image boundaries.
For non-antialiased lines with integer coordinates, the 8 connected or 4 connected Bresenham algorithm.
Thick lines are drawn with rounding endings.
Antialiased lines are drawn using Gaussian filtering.

image: image
start: first point of the line segment
end: second point of the line segement
color: line color
thickness: line thickness
type: type of the line.
shift: number of fractional bits in the point coordinates
