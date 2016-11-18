#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
#include <math.h>
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
Mat transformation(Mat input ) {

	//對其直方圖做均值化  
	//先計算各灰階值出現的機率
	//並計算其累積機率與最小灰階值
	//對其均值化
	int mn = input.rows*input.cols;
	double nt[256] = { 0 };
	double pt[256] = {0};
	double st[256] = { 0 };
	int h[256] = { 0 };
	int stmin = -1;

	//統計各灰階值出現次數
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			nt[input.at<uchar>(i, j)]++;
		}
	}

	//計算其累積次數
	pt[0] = nt[0];
	st[0] = pt[0];
	if (st[0] > 0) {
		stmin = 0;
	}
	for (int i = 1; i < 256; i++) {
		
		pt[i] = nt[i];
		st[i] = st[i - 1] + pt[i];
		if (stmin == -1 && st[i] > 0) {
			stmin = i;
		}
		
	}
	

	//根據式子算出灰階值的均值化換算表
	for (int i = stmin; i < 256; i++) {
		h[i]= (int)((st[i] - st[stmin]) / (mn - st[stmin]) * 255+0.5);
		
	}

	//將各pixel的灰階查表轉換
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			input.at<uchar>(i, j) = h[input.at<uchar>(i, j)];
		}
	}

	return input;
}
int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Origin Image/Fig03_Slide22.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat OutImg1 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	
	//複製圖片
	OutImg1 = copyImg(SrcImg);

	//轉換圖片
	OutImg1 = transformation(OutImg1);
	// Show images	
	imshow("Input Image", SrcImg);
	imshow("Output Image_1", OutImg1);

	// Write output images
	imwrite("Histogram Equalization/Output.tif", OutImg1);

	
	waitKey(0);
	return 0;
}