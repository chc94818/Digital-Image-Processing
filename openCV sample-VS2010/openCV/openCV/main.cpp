#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;

int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Fig3.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Create a grayscale output image matrix
	Mat DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);

	// Copy each pixel of the source image to the output image
	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg.at<uchar>(i,j)=SrcImg.at<uchar>(i,j);
		}

	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image", DstImg);

	// Write output images
	imwrite("Fig3_output.tif", DstImg);
	
	waitKey(0);
	return 0;
}