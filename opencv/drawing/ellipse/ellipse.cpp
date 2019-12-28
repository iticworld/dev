#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define width  400
#define height 400

using namespace cv;

int main(void)
{
  const char * window = "ellipse";
  Mat image(width, height, CV_8UC3);
  cv::ellipse(image, Point(width/2, height/2), Size(width/4, height/16),   0, 0, 360, Scalar(255, 0, 0), 1, LINE_8);
  cv::ellipse(image, Point(width/2, height/2), Size(width/4, height/16),  90, 0, 360, Scalar(255, 0, 0), 1, LINE_8);
  cv::ellipse(image, Point(width/2, height/2), Size(width/4, height/16),  45, 0, 360, Scalar(255, 0, 0), 1, LINE_8);
  cv::ellipse(image, Point(width/2, height/2), Size(width/4, height/16), -45, 0, 360, Scalar(255, 0, 0), 1, LINE_8);
  imshow(window, image);
  waitKey();
  return 0;
}
