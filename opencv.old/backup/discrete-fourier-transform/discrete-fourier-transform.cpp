#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
  Mat input = imread("anise.png", IMREAD_GRAYSCALE);
  Mat padded;
  // expand input image to optimal size
  int m = getOptimalDFTSize(input.rows);
  int n = getOptimalDFTSize(input.cols);
  // on the border add zero values
  copyMakeBorder(input, padded, 0, m - input.rows, 0, n - input.cols, BORDER_CONSTANT, Scalar::all(0));

  Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
  Mat complex;
  // add to the expanded another plane with zeros
  merge(planes, 2, complex);
  // this way the result may fit in the source matrix
  dft(complex, complex);
  // compute the magnitude and switch to logarithmic scale log(1 + sqrt(real(dft(input))^2 + imaginary(dft(input))^2))
  split(complex, planes);     // planes[0] = real(dft(input)), planes[1] = imaginary(dft(input))
  magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
  Mat magnitude = planes[0];

  magnitude += Scalar::all(1);
  // switch to logarithmic scale
  log(magnitude, magnitude);

  // crop the spectrum, if it has an odd number of rows or columns
  magnitude = magnitude(Rect(0, 0, magnitude.cols & -2, magnitude.rows & -2));
  // rearrange the quadrants of fourier image so that the origin is at the image center
  int cx = magnitude.cols/2;
  int cy = magnitude.rows/2;

  // create a region of interest per quadrant
  Mat quadrant[4] = {
    Mat(magnitude, Rect( 0,  0, cx, cy)),
    Mat(magnitude, Rect(cx,  0, cx, cy)),
    Mat(magnitude, Rect( 0, cy, cx, cy)),
    Mat(magnitude, Rect(cx, cy, cx, cy))
  };
  Mat tmp;

  quadrant[0].copyTo(tmp);
  quadrant[3].copyTo(quadrant[0]);
  tmp.copyTo(quadrant[3]);
  quadrant[1].copyTo(tmp);
  quadrant[2].copyTo(quadrant[1]);
  tmp.copyTo(quadrant[2]);

  // Transform the matrix with float value into a viewable image form (float between values 0 and 1).
  normalize(magnitude, magnitude, 0, 1, NORM_MINMAX);

  imshow("input", input);
  imshow("spectrum magnitude", magnitude);
  waitKey();
  return 0;
}
