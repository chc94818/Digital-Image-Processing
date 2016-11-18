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
Mat transformation(Mat input ,double g) {
	Mat tImg;
	//�ھ� S = C*R^g 
	//�d��0~255 �Dc
	double c = 255 / pow(255, g);

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			//��C��pixel���Ƕ��� R �N�J�禡�D S
			input.at<uchar>(i, j) = c*pow(input.at<uchar>(i, j), g);
		}
	}
	tImg = input;
	return tImg;
}
int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Origin Image/Fig01_Slide10.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat OutImg1 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat OutImg2 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat OutImg3 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	
	//�ƻs�Ϥ�
	OutImg1 = copyImg(SrcImg);
	OutImg2 = copyImg(SrcImg);
	OutImg3 = copyImg(SrcImg);

	//�ഫ
	OutImg1 = transformation(OutImg1, 3);
	OutImg2 = transformation(OutImg2, 4);
	OutImg3 = transformation(OutImg3, 5);
	// Show images	
	imshow("Input Image", SrcImg);
	imshow("Output Image_1", OutImg1);
	imshow("Output Image_2", OutImg2);
	imshow("Output Image_3", OutImg3);

	// Write output images
	imwrite("Intensity Transform/intensity_1.tif", OutImg1);
	imwrite("Intensity Transform/intensity_2.tif", OutImg2);
	imwrite("Intensity Transform/intensity_3.tif", OutImg3);

	
	waitKey(0);
	return 0;
}