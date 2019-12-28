#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

#define width  400
#define height 400

int main()
{
  const char * window = "line";
  Mat image(width, height, CV_8UC3);

  line(image, Point(width/2, height/2), Point(width/4, height/4), Scalar(255, 255, 255), 1, LINE_8);

  imshow(window, image);
  waitKey();
  return 0;
}
