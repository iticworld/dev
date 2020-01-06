#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int alpha = 100;
int beta = 0;

// input
Mat input;
// output
Mat output;

static void onChange();

static void onBrightness(int value, void *)
{
  beta = value;
  onChange();
}

static void onContrast(int value, void *)
{
  alpha = value;
  onChange();
}

static void onChange()
{
  double _alpha = (double)(alpha) / 100;
  for(int y = 0; y < input.rows; y++) {
    for(int x = 0; x < input.cols; x++) {
      for(int c = 0; c < input.channels(); c++) {
        output.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(_alpha * input.at<Vec3b>(y, x)[c] + beta);
      }
    }
  }

  imshow("multiplication and addition", output);
}

static void onTrackbar(int value, void *)
{
  double a = (double) (value) / 100;
  beta = value;

  onChange();
}

int main()
{
  input = imread("first.jpg");
  output = Mat::zeros(input.size(), input.type());

  // create window
  namedWindow("multiplication and addition", WINDOW_AUTOSIZE);
  createTrackbar("contrast", "multiplication and addition", &alpha, 100, onContrast);
  createTrackbar("brightness", "multiplication and addition", &beta, 255, onBrightness);

  imshow("multiplication and addition", input);

  waitKey(0);

  return 0;
}
