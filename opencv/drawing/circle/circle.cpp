#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

#define width  400
#define height 400

int main(void)
{
  const char * window = "circle";
  Mat image(width, height, CV_8UC3);

  circle(image, Point(width/2, height/2), width/4, Scalar(0, 0, 255), FILLED, LINE_8);

  imshow(window, image);
  waitKey();
  return 0;
}
