#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{
  Mat input = imread("anise.png", IMREAD_GRAYSCALE);

  Mat padded;   // expand input image to optimal size
  int m = getOptimalDFTSize(input.rows);
  int n = getOptimalDFTSize(input.cols);
  // on the border add zero values
  copyMakeBorder(input, padded, 0, m - input.rows, 0, n - input.cols, BORDER_CONSTANT, Scalar::all(0));

  Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
  Mat complex;
  merge(planes, 2, complex);      // add to expanded another plane with zeros
  dft(complex, complex);          // this way the result may fit in the source matrix

  // compute the magnitude and switch to logarithmic scale
  // => log(1 + sqrt(Re(DFT(input))^2 + Im(DFT(input))^2))
  split(complex, planes);       // planes[0] = Re(DFT(input), planes[1] = Im(DFT(input))
  Mat mag = planes[0];

  mag += Scalar::all(1);        // switch to logarithmic scale
  log(mag, mag);

  // crop the spectrum, if it has an odd number of rows or columns
  mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

  // rearrnage the quadrants of Fourier image so that the origin is at the image center
  int cx = mag.cols/2;
  int cy = mag.rows/2;

  Mat q0(mag, Rect(0, 0, cx, cy));    // Top left - create a Region of Interest per quadrant
  Mat q1(mag, Rect(cx, 0, cx, cy));   // Top right
  Mat q2(mag, Rect(0, cy, cx, cy));   // Bottom left
  Mat q3(mag, Rect(cx, cy, cx, cy));  // Bottom-Right

  // swap quadrants (Top Left with Bottom Right)
  Mat tmp;
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  // swap quadrant (Top Right with Bottom Left)
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
  // Transform the mtraix with float values into a viewable image form (float between values 0 and 1).
  normalize(mag, mag, 0, 1, NORM_MINMAX);

  imshow("input", input);
  imshow("spectrum magnitude", mag);

  waitKey();
  return 0;
}
