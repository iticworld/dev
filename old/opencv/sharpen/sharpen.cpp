#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void Sharpen(const Mat & image, Mat & result);

int main(int argc, char ** argv)
{
  if(argc < 2)
  {
    cout << "image path is not described."<<endl;
    return -1;
  }
  const char * name = argv[1];

  Mat src;
  Mat dest;

  if(argc >= 3 && !strcmp("G", argv[2]))
  {
    src = imread(name, IMREAD_GRAYSCALE);
  }
  else
  {
    src = imread(name, IMREAD_COLOR);
  }

  if(src.empty())
  {
    cerr << "can't open image [" << name << "]" <<endl;
    return -1;
  }

  namedWindow("input", WINDOW_AUTOSIZE);
  namedWindow("output", WINDOW_AUTOSIZE);

  imshow("input", src);
  double t = (double) getTickCount();

  Sharpen(src, dest);

  t = ((double) getTickCount() - t) / getTickFrequency();
  cout << "Hand written function time passed in seconds: " << t << endl;

  imshow("output", dest);

  waitKey(0);
  return 0;
}

static void Sharpen(const Mat & image, Mat & result)
{
  CV_Assert(image.depth() == CV_8U);  // accept only uchar images
  const int nChannels = image.channels();
  result.create(image.size(), image.type());

  for(int i = 1; i < image.rows - 1; ++i)
  {
    const uchar * previous = image.ptr<uchar>(i - 1);
    const uchar * current  = image.ptr<uchar>(i    );
    const uchar * next     = image.ptr<uchar>(i + 1);

    uchar * output = result.ptr<uchar>(i);

    for(int j = nChannels; j < nChannels * (image.cols - 1); ++j)
    {
      *output++ = saturate_cast<uchar>(5 * current[j] - current[j - nChannels] - current[j + nChannels] - previous[j] - next[j]);
    }
  }

  result.row(0).setTo(Scalar(0));
  result.row(result.rows - 1).setTo(Scalar(0));
  result.col(0).setTo(Scalar(0));
  result.col(result.cols - 1).setTo(Scalar(0));
}
