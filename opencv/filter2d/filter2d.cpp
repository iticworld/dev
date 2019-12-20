#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{
  if(argc < 2)
  {
    cout << "image path is not specified."<<endl;
    return -1;
  }
  const char * name = argv[1];

  Mat src;
  Mat dest;

  if(argc >=3 && !strcmp("G", argv[2]))
  {
    src = imread(name, IMREAD_GRAYSCALE);
  }
  else
  {
    src = imread(name, IMREAD_COLOR);
  }

  if(src.empty())
  {
    cerr << "can't open image [" << name << "]" << endl;
    return -1;
  }

  namedWindow("input", WINDOW_AUTOSIZE);
  namedWindow("output", WINDOW_AUTOSIZE);

  imshow("input", src);

  Mat kernel = (Mat_<char>(3, 3) <<  0, -1,  0,
                                    -1,  5, -1,
                                     0, -1,  0);

  double t = (double) getTickCount();
  cout << "depth" << src.depth() << endl;
  filter2D(src, dest, src.depth(), kernel);
  t = ((double) getTickCount() - t) / getTickFrequency();
  cout << "Built-in filter2D time passed in seconds: " << t << endl;

  imshow("output", dest);
  waitKey(0);
  return 0;
}
