#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define width 400
#define atom 0
#define rook 1

using namespace cv;

static void _ellipse(Mat image, double angle);
static void _circle(Mat image, Point center);
static void _polygon(Mat image);
static void _line(Mat image, Point start, Point end);

int main()
{
  const char * window[] = { "atom", "rook" };
  Mat image[] = { Mat::zeros(width, width, CV_8UC3), Mat::zeros(width, width, CV_8UC3) };

  _ellipse(image[atom], 90);
  _ellipse(image[atom], 0);
  _ellipse(image[atom], 45);
  _ellipse(image[atom], -45);
  imshow(window[atom], image[atom]);
  waitKey();
  return 0;
}

static void _ellipse(Mat image, double angle)
{
  int thickness = 2;
  int type = 8;

  ellipse(image, Point(width/2, width/2), Size(width/4, width/16), angle, 0, 360, Scalar(255, 0, 0), thickness, type);
}
