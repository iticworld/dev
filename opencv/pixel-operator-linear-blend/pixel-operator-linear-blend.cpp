#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include <unistd.h>

using namespace cv;

Mat input[2];
Mat output;

static void performLinearBlend(double value)
{
  for(int y = 0; y < input[0].rows; y++)
  {
    for(int x = 0; x < input[0].cols; x++)
    {
      for(int c = 0; c < input[0].channels(); c++)
      {
        output.at<Vec3b>(y, x)[c] = (1.0f - value) * input[0].at<Vec3b>(y, x)[c] + value * input[1].at<Vec3b>(y, x)[c];
      }
    }
  }
  imshow("output", output);
}

int main()
{
  input[0] = imread("first.jpg");
  input[1] = imread("second.jpg");
  output = Mat::zeros(input[0].size(), input[0].type());

  namedWindow("output", WINDOW_AUTOSIZE);

  for(int i = 1; i < 100; i++)
  {
    performLinearBlend((double) i / 100);
    waitKey(50);
  }

  waitKey();
  return 0;
}
