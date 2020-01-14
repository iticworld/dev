#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

/**
 *  g++ -std=c++14 -o example.out example.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_highgui -lopencv_imgcodecs -lopencv_core
 */
int main()
{
  Mat source = imread("anise.png");
  Mat destination;
  imshow("source", source);
  for(int i = 1; i < 31; i = i + 2)
  {
    blur(source, destination, Size(i, i), Point(-1, -1));
    imshow("destination", destination);
    waitKey(5000);
  }
  waitKey();
  return 0;
}
