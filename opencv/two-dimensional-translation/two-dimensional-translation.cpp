#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;

int main()
{
  Mat input = imread("anise.png");
  const int x = 25;
  const int y = 50;
  Mat output(input.size() + Size(x, y), input.type(), Scalar());
  imshow("input", input);


  int64_t begin = getTickCount();

  for(int j = 0; j < input.rows; j++)
  {
    for(int i = 0; i < input.cols; i++)
    {
      // if(j + y < input.rows && i + x < input.cols)
      {
        output.at<Vec3b>(j + y, i + x) = input.at<Vec3b>(j, i);
      }
    }
  }
  int64_t end = getTickCount();
  double result = (double)(end - begin) / getTickFrequency();
  std::cout<<result<<std::endl;
  imshow("output", output);
  /**
   * Size(width, height)
   */
  Mat translation(Size(3, 2), CV_64FC1);
  translation.at<double>(0, 0) = 1;
  translation.at<double>(0, 1) = 0;
  translation.at<double>(0, 2) = x;
  translation.at<double>(1, 0) = 0;
  translation.at<double>(1, 1) = 1;
  translation.at<double>(1, 2) = y;
  std::cout << translation << std::endl;

  Mat affine;
  begin = getTickCount();
  warpAffine(input, affine, translation, input.size() + Size(x, y));
  end = getTickCount();
  result = (double)(end - begin) / getTickFrequency();
  std::cout<<result<<std::endl;
  imshow("affine", affine);

  waitKey(0);
  return 0;
}
