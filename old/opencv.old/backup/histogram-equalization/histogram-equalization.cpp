/**
 * g++ -o histogram-equalization.out histogram-equalization.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_core
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char ** argv)
{
  Mat src = imread("anise.png", IMREAD_COLOR);
  cvtColor(src, src, COLOR_BGR2GRAY);

  Mat dst;

  equalizeHist(src, dst);

  imshow("source", src);
  imshow("equalized", dst);

  waitKey();

  return 0;
}
