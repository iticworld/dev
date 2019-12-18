#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char ** argv)
{
  char * name = argv[1];

  Mat image;
  image = imread(name, IMREAD_COLOR);

  if(argc != 2 || !image.data)
  {
    printf("no image data\n");
    return -1;
  }

  Mat gray;
  cvtColor(image, gray, COLOR_BGR2GRAY);

  imwrite("./gray.jpg", gray);

  namedWindow(name, WINDOW_AUTOSIZE);
  namedWindow("gray", WINDOW_AUTOSIZE);

  imshow(name, image);
  imshow("gray", gray);

  waitKey(0);

  return 0;
}
