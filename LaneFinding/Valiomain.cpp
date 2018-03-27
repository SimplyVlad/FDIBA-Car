#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;

cv::Mat gray, frame, output, edges;

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
		cv::cvtColor(frame, gray, CV_BGR2GRAY);
		cv::threshold(gray, output, 150, 255, cv::THRESH_BINARY);

		GaussianBlur(output, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		
		namedWindow("normal camera", WINDOW_AUTOSIZE);
		namedWindow("edges", WINDOW_AUTOSIZE);
		namedWindow("binary", WINDOW_AUTOSIZE);
		imshow("normal camera", frame);
		imshow("edges", edges);
		imshow("binary", output);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
