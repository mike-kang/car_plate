// CarPlate.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"



#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void draw_houghLines(Mat src, Mat&dst, vector<Vec2f>& lines, int nline)
{
	cvtColor(src, dst, CV_GRAY2BGR);
	for (size_t i = 0; i < min((int)lines.size(), nline); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		Point2d pt(a*rho, b* rho);
		Point2d delta(1000 * -b, 1000 * a);
		line(dst, pt + delta, pt - delta, Scalar(0, 255, 0), 1, LINE_AA);
	}

}

int main()
{
	cv::Mat image; // create an empty image
	image = cv::imread("capture.jpg");
	if (image.empty()) { // error handling
						 // no image has been created…
						 // possibly display an error message
						 // and quit the application
		cv::waitKey(0);
	}
	cv::Mat roi;
	Range r_col(2575, 2575 + 317), r_row(2097, 2097 + 254);
	roi = image(r_row, r_col);


	// define the window (optional)
	cv::namedWindow("Original Image");
	// show the image
	//cv::imshow("Original Image", image);
	cv::imshow("roi", roi);

	//canny
	Mat canny;
	Canny(roi, canny, 150, 150);
	cv::imshow("canny", canny);

	//hough
	Mat dst;
	double rho = 1, theta = CV_PI / 180;
	std::vector<Vec2f> lines;
	HoughLines(canny, lines, rho, theta, 50);
	draw_houghLines(canny, dst, lines, 10);
	cv::imshow("hough", dst);

	cv::waitKey(0);
	return 0;
}