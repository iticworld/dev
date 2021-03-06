#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    printf("usage: display <image path>\n");
    return -1;
  }

  Mat image = imread(argv[1], IMREAD_COLOR);

  if(!image.data)
  {
    printf("no image data\n");
    return -1;
  }

  namedWindow("display", WINDOW_NORMAL);
  imshow("display", image);

  waitKey(0);

  return 0;
}
