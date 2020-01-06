#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
  double alpha = 0.5;
  double beta;
  double input;

  Mat first;
  Mat second;
  Mat dest;

  std::cout << " Simple Linear Blender " << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "* Enter alpha [0.0 ~ 1.0]: ";
  std::cin >> input;

  // We use the alpha provided by the user if it is between 0 and 1
  if(input >= 0 && input <= 1)
  {
    alpha = input;
  }

  first = imread("LinuxLogo.jpg");
  second = imread("WindowsLogo.jpg");

  if(first.empty())
  {
    std::cout << "Error loading first" << std::endl;
    return -1;
  }

  if(second.empty())
  {
    std::cout << "Error loading second" << std::endl;
    return -1;
  }

  beta = (1.0f - alpha);
  addWeighted(first, alpha, second, beta, 0.0f, dest);

  imshow("Linear Blend", dest);
  waitKey(0);

  return 0;
}
