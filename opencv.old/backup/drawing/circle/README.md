CIRCLE
======

```c++
#include <opencv2/imgproc.hpp>

void cv::circle(InputOutputArray image,
                Point            center,
                int              radius,
                const Scalar &   color,
                int              thickness = 1,
                int              type = LINE_8,
                int              shift  0)
```

Draws a circle.

The function cv::circle draws a simple or filled circle with a given center and radius.

## PARAMETER

| PARAMETER | TYPE | DESCRIPTION |
| --------- | ---- | ----------- |
| image     | InputOutputArray | image where the circle is drawn. |
| center    | Point            | center of the circle.            |
| radius    | int              | radius of the circle.            |
| color     | const Scalar &   | circle color.                    |
| thickness | int              | thickness of the circle outline, if positive, Negative values, like FILLED, mean that a filled circle is to be drawn. |
| type      | int              | type of the circle boundary.     |
| shift     | int              | number of fractional bits in the coordinates of the center and in the radius value. |

## BUILD

```
g++ -o circle.out circle.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_imgproc -lopencv_highgui -lopencv_core
```
