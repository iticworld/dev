#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const int number = 100;
const int delay = 5;

const int width = 900;
const int height = 600;
int x[2] = { -width / 2, 3 * width / 2 };
int y[2] = { -height / 2, 3 * height / 2 };

namespace _random {
  static Scalar color(RNG & rng);
  static void lines(Mat image, const char * wndow, RNG & rng);
  static void rectangles(Mat image, const char * window, RNG & rng);
  static void polygons(Mat image, const char * window, RNG & rng);
  static void ellipses(Mat image, const char * window, RNG & rng);
}


int main()
{
  const char * window = "random";
  RNG rng(0xFFFFFFFF);
  Mat image = Mat::zeros(height, width, CV_8UC3);
  imshow(window, image);
  waitKey(delay);
  _random::lines(image, window, rng);
  _random::rectangles(image, window, rng);
  _random::polygons(image, window, rng);
  _random::ellipses(image, window, rng);

  return 0;
}

namespace _random {
  static Scalar color(RNG & rng)
  {
    int c = rng;
    return Scalar(c & 255, (c >> 8) & 255, (c >> 16) & 255);
  }
  static void lines(Mat image, const char * window, RNG & rng)
  {
    Point start;
    Point end;
    for(int i = 0; i < number; i++)
    {
      start.x = rng.uniform(x[0], x[1]);
      start.y = rng.uniform(y[0], y[1]);
      end.x = rng.uniform(x[0], x[1]);
      end.y = rng.uniform(y[0], y[1]);

      line(image, start, end, _random::color(rng), rng.uniform(1, 10), LINE_8);
      imshow(window, image);
      waitKey(delay);
    }
  }

  static void rectangles(Mat image, const char * window, RNG & rng)
  {
    Point start;
    Point end;
    for(int i = 0; i < number; i++)
    {
      start.x = rng.uniform(x[0], x[1]);
      start.y = rng.uniform(y[0], y[1]);
      end.x = rng.uniform(x[0], x[1]);
      end.y = rng.uniform(y[0], y[1]);

      rectangle(image, start, end, _random::color(rng), max(rng.uniform(-3, 10), -1), LINE_8);
      imshow(window, image);
      waitKey(delay);
    }
  }

  static void polygons(Mat image, const char * window, RNG & rng)
  {
    for(int i = 0; i < number; i++)
    {
      Point points[2][3];
      for(int _x = 0; _x < 2; _x++)
      {
        for(int _y = 0; _y < 3; _y++)
        {
          points[_x][_y].x = rng.uniform(x[0], x[1]);
          points[_x][_y].y = rng.uniform(y[0], y[1]);
        }
      }
      const Point * ppt[2] = { points[0], points[1] };
      int npt[]= { 3, 3};

      polylines(image, ppt, npt, 2, true, _random::color(rng), rng.uniform(1, 10), LINE_8);
      imshow(window, image);
      waitKey(delay * 2);
    }
  }

  static void ellipses(Mat image, const char * window, RNG & rng)
  {
    for(int i = 0; i < number; i++)
    {
      Point center;
      center.x = rng.uniform(x[0], x[1]);
      center.y = rng.uniform(y[0], y[1]);

      Size axes;
      axes.width = rng.uniform(0, 200);
      axes.height = rng.uniform(0, 200);

      double angle = rng.uniform(0, 180);

      ellipse(image, center, axes, angle, angle - 100, angle + 200, _random::color(rng), rng.uniform(-1, 9), LINE_8);
      imshow(window, image);
      waitKey(delay);
    }
  }
}
