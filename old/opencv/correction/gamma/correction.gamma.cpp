#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

Mat original;
Mat corrected;
Mat gamma_corrected;

int gAlpha = 100;
int gBeta = 100;
int gGamma = 100;

static void basic_linear_transform(const Mat & image, const double alpha, const int beta)
{
  Mat res;
  image.convertTo(res, -1, alpha, beta);

  hconcat(image, res, corrected);

  imshow("linear", corrected);
}

static void gamma_correction(const Mat & img, const double gamma)
{
  CV_Assert(gamma >= 0);
  Mat table(1, 256, CV_8U);
  uchar * p = table.ptr();
  for(int i = 0; i < 256; ++i) {
    p[i] = saturate_cast<uchar>(pow(i / 255.0f, gamma) * 255.0f);
  }
  Mat res = img.clone();
  LUT(img, table, res);

  hconcat(img, res, gamma_corrected);

  imshow("gamma", gamma_corrected);
}

void on_linear_transform_alpha_trackbar(int, void *)
{
  double alpha = gAlpha / 100.0f;
  int beta = gBeta - 100;
  basic_linear_transform(original, alpha, beta);
}

void on_linear_transform_beta_trackbar(int, void *)
{
  double alpha = gAlpha / 100.0f;
  int beta = gBeta - 100;
  basic_linear_transform(original, alpha, beta);
}

void on_gamma_correction_trackbar(int, void *)
{
  double gamma = gGamma / 100.0f;
  gamma_correction(original, gamma);
}

int main(int argc, char ** argv)
{
  original = imread("anise.png");
  corrected = Mat(original.rows, original.cols * 2, original.type());
  gamma_corrected = Mat(original.rows, original.cols * 2, original.type());

  hconcat(original, original, corrected);
  hconcat(original, original, gamma_corrected);

  namedWindow("linear");
  namedWindow("gamma");

  createTrackbar("Alpha gain (contrast)", "linear", &gAlpha, 500, on_linear_transform_alpha_trackbar);
  createTrackbar("Beta bias (brightness)", "linear", &gBeta, 200, on_linear_transform_beta_trackbar);
  createTrackbar("Gamma correction", "gamma", &gGamma, 200, on_gamma_correction_trackbar);

  on_linear_transform_alpha_trackbar(0, 0);
  on_gamma_correction_trackbar(0, 0);

  waitKey();

  return 0;
}
