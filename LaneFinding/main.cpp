#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace cv::cuda;

cv::Mat imageROI, gray, frame, binary, canny, Perspective_Matrix(2, 4, CV_32FC1), Perspective_Matrix_inverse, Perspective;
Point2f inputRect[4];
Point2f outputRect[4];

int main()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	while (1)
	{
		cap >> frame; // get a new frame from camera
				
		Perspective_Matrix = Mat::zeros(frame.rows, frame.cols, frame.type());
	
		inputRect[0] = Point2f(0, 0);
		inputRect[1] = Point2f(frame.cols, 0);
		inputRect[2] = Point2f(frame.cols, frame.rows);
		inputRect[3] = Point2f(0, frame.rows);
														   
		outputRect[0] = Point2f(0, 0);
		outputRect[1] = Point2f(frame.cols, 0);
		outputRect[2] = Point2f(frame.cols - 210, frame.rows);
		outputRect[3] = Point2f(210, frame.rows);
		
		Perspective_Matrix = getPerspectiveTransform(inputRect, outputRect);
		invert(Perspective_Matrix, Perspective_Matrix_inverse);

		warpPerspective(frame, Perspective, Perspective_Matrix, frame.size());
		imageROI = Perspective.clone();
		Perspective = Perspective(Rect(0, 200, Perspective.cols, (Perspective.rows - 200)));

		cv::cvtColor(Perspective, gray, CV_BGR2GRAY);
		cv::threshold(gray, binary, 160, 255, cv::THRESH_BINARY);

		GaussianBlur(binary, canny, Size(7, 7), 1.5, 1.5);
		Canny(canny, canny, 0, 30, 3);


		namedWindow("normal camera", WINDOW_AUTOSIZE);
		namedWindow("edges", WINDOW_AUTOSIZE);
		namedWindow("binary", WINDOW_AUTOSIZE);
		namedWindow("perspective", WINDOW_AUTOSIZE);
		imshow("normal camera", frame);
		imshow("edges", canny);
		imshow("binary", binary);
		imshow("perspective", imageROI);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
