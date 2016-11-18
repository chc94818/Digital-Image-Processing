#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
#include <math.h>
using namespace std;
using namespace cv;
//�ƻs�Ϥ�
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

//�ഫ�B��
Mat transformation(Mat input ) {

	//��䪽��ϰ����Ȥ�  
	//���p��U�Ƕ��ȥX�{�����v
	//�íp���ֿn���v�P�̤p�Ƕ���
	//��䧡�Ȥ�
	int mn = input.rows*input.cols;
	double nt[256] = { 0 };
	double pt[256] = {0};
	double st[256] = { 0 };
	int h[256] = { 0 };
	int stmin = -1;

	//�έp�U�Ƕ��ȥX�{����
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			nt[input.at<uchar>(i, j)]++;
		}
	}

	//�p���ֿn����
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
	

	//�ھڦ��l��X�Ƕ��Ȫ����Ȥƴ����
	for (int i = stmin; i < 256; i++) {
		h[i]= (int)((st[i] - st[stmin]) / (mn - st[stmin]) * 255+0.5);
		
	}

	//�N�Upixel���Ƕ��d���ഫ
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
	
	//�ƻs�Ϥ�
	OutImg1 = copyImg(SrcImg);

	//�ഫ�Ϥ�
	OutImg1 = transformation(OutImg1);
	// Show images	
	imshow("Input Image", SrcImg);
	imshow("Output Image_1", OutImg1);

	// Write output images
	imwrite("Histogram Equalization/Output.tif", OutImg1);

	
	waitKey(0);
	return 0;
}