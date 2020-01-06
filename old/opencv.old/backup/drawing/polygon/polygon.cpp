#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

#define width  400
#define height 400

int main()
{
  const char * window = "polygon";
  Mat image(width, height, CV_8UC3);

  Point rook[1][20] = {
    {
      Point(    width/4,   7*height/8 ),
      Point(  3*width/4,   7*height/8 ),
      Point(  3*width/4,  13*height/16),
      Point( 11*width/16, 13*height/16),
      Point( 19*width/32,  3*height/8 ),
      Point(  3*width/4,   3*height/8 ),
      Point(  3*width/4,     height/8 ),
      Point( 26*width/40,    height/8 ),
      Point( 26*width/40,    height/4 ),
      Point( 22*width/40,    height/4 ),
      Point( 22*width/40,    height/8 ),
      Point( 18*width/40,    height/8 ),
      Point( 18*width/40,    height/4 ),
      Point( 14*width/40,    height/4 ),
      Point( 14*width/40,    height/8 ),
      Point(    width/4,     height/8 ),
      Point(    width/4,   3*height/8 ),
      Point( 13*width/32,  3*height/8 ),
      Point(  5*width/16, 13*height/16),
      Point(    width/4,  13*height/16)
    }
  };
  int npt[] = { 20 };
  const Point * ppt[1] = { rook[0] };

  fillPoly(image, ppt, npt, 1, Scalar(255, 255, 255), LINE_8);

  imshow(window, image);
  waitKey();
  return 0;
}
