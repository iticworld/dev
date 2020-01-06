#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char ** argv)
{
  CommandLineParser parser(argc, argv, "{@input | lena.jpg | input image}");
  Mat image = imread(parser.get<String>("@input"));
  if(image.empty())
  {
    std::cout << "Could not open or find the image!" << std::endl;
    std::cout << "Usage: " << argv[0] << " <input image>" << std::endl;
    return -1;
  }

  Mat dest = Mat::zeros(image.size(), image.type());

  double alpha = 2.1f;    // simple contrast control
  int beta = 50;          // simple brightness control

  for(int y = 0; y < image.rows; y++)
  {
    for(int x = 0; x < image.cols; x++)
    {
      for(int c = 0; c <image.channels(); c++)
      {
        dest.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
      }
    }
  }

  imshow("Original Image", image);
  imshow("New Image", dest);

  waitKey();

  return 0;
}
