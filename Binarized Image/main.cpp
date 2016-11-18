#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
#include <math.h>
#include <string.h>
using namespace std;
using namespace cv;
//複製圖片
Mat copyImg(Mat input) {
	Mat tImg = Mat(input.rows, input.cols, CV_8UC1);
	// Copy each pixel of the source image to the output image
	for (int i = 0; i<input.rows; ++i)
		for (int j = 0; j<input.cols; ++j)
		{
			tImg.at<uchar>(i, j) = input.at<uchar>(i, j);
		}

	return tImg;
}
//轉換運算
Mat transformation(Mat input ,int b) {
	//求 bitplane b
	Mat tImg;

	//灰階值mod 2^b < 2^(b-1) 設為0 反之為255
	int mask = pow(2, b);
	int bound = pow(2, b-1);

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
				
			if (input.at<uchar>(i, j) % mask < bound) {
			
				input.at<uchar>(i, j) = 0;
			}
			else {
				input.at<uchar>(i, j) = 255;
			}
		}
	}
	tImg = input;
	return tImg;
}
int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Origin Image/Fig02_Slide14.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat OutImg[8];
	//顯示原圖
	imshow("Input Image", SrcImg);

	//對bitplane 1~8 分別運算並顯示
	for (int i = 0; i < 8; i++) {
		OutImg[i]= (SrcImg.rows, SrcImg.cols, CV_8UC1);
		OutImg[i] = copyImg(SrcImg);
		OutImg[i] = transformation(OutImg[i], i+1);
		char title[100];
		sprintf(title, "Output Image_%d", i+1);
		// Show images	
		imshow(title, OutImg[i]);
		char name[100];
		sprintf(name, "Binarized Image/bitPlane_%d.tif", i + 1);
		// Write output images
		imwrite(name, OutImg[i]);
	}
	
	
	
	waitKey(0);
	return 0;
}