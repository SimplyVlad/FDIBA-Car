#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Image.h"
#include <iostream> 
#include <vector>
#include "polyfit.hpp"
#include <string>

using namespace std;

using namespace cv;

 
 
//find the beginning of left line in the image
//parameter is Mat with bird view 
int findLeftLine(const Mat& leftSide);


//find the beginning of right line in the image
//parameter is Mat with bird view 
int findRightLine(const Mat& rightSide);

/*
//iterate through columns in the left side of the image to find the column with the most 255 values
//returned x will be the beginning of left line 
int histogramPeakLeft(const Mat& leftSide);

//iterate through columns in the right side of the image to find the column with the most 255 values
//returned x will be the beginning of right line 
int histogramPeakRight(const Mat& rightSide);
*/


Mat imageROI, gray, frame, binary, gaussian, canny, Perspective_Matrix(2, 4, CV_32FC1), Perspective_Matrix_inverse, Perspective;

Point2f inputRect[4];
Point2f outputRect[4];

int main() {
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

		GaussianBlur(binary, gaussian, Size(7, 7), 1.5, 1.5);
		Canny(gaussian, canny, 0, 30, 3);



		namedWindow("normal camera", WINDOW_AUTOSIZE);
		namedWindow("edges", WINDOW_AUTOSIZE);
		namedWindow("binary", WINDOW_AUTOSIZE);
		namedWindow("perspective", WINDOW_AUTOSIZE);
		imshow("normal camera", frame);
		imshow("edges", canny);
		imshow("binary", binary);
		imshow("perspective", imageROI);
		if (waitKey(30) >= 0) break;

		//test
		cout << "LEFT: " << findLeftLine(canny) << endl;
		cout << "LEFT: " << findRightLine(canny) << endl;



	}



	return 0;
}


	//POLYFIT - HOW TO USE
	 /*
	 
	vector<double> xV = {0, 1,2,3,4 };
	vector<double> yV = {0, 1,2,1,-1 };

	vector<double> coeff = mathalgo::polyfit(xV, yV, 3);
	 
	// ...
	for (std::vector<double>::const_iterator i = coeff.begin(); i != coeff.end(); ++i)
		std::cout << *i << ' ';

	 

	vector<double> checkYforGivenX = { 4,6,10 };
	vector<double> checkedY = mathalgo::polyval(coeff, checkYforGivenX);

	cout << endl;
	for (std::vector<double>::const_iterator i = checkedX.begin(); i != checkedX.end(); ++i)
		std::cout << *i << ' ';
		*/
	 
	 
 


//algorithm: search for 255 value to find the left side of the left line and set leftOfLine to that x
//search 80 pixels to the right for 255 value to see if the right side of the left line will be encountered, 
//if yes - beginning of left line is found return middle 
//if 255 value is encountered in less than 22 pixels to the right, than its distance is too small for right side
//of the line, it is probably noise, continue with new search with Y-axis decreased by 20
int findLeftLine(const Mat& leftSide) {
	int nRow = leftSide.rows;  // y-axis
	
	int leftOfLine =0, rightOfLine =0;
	
	//start at bottom left
	for (int y = nRow;y > 360;y -= 20) {
		for (int x = 20;x < 100;x++) {
			if (leftSide.at<uchar>(Point(x, y)) == 255) {
				if (leftOfLine == 0) {
					leftOfLine = x;
					continue;
				}
				else if (rightOfLine == 0) {
					if ((rightOfLine - leftOfLine) < 12)
						continue;
					else {
						rightOfLine = x;
						break;
					}
				}


			}
			
		}
		leftOfLine = 0;
		rightOfLine = 0;
	}
	return (leftOfLine + rightOfLine) / 2;
}


//algorithm: search for 255 value to find the left side of the right line and set leftOfLine to that x
//search 90 pixels to the right for 255 value to see if
//the right side of the right line will be encountered, if yes - beginning of right line is found return middle 
//if 255 value is encountered in less than 22 pixels to the right, than its distance is too small for right 
//side of the line, it is probably noise, continue with new search with Y-axis decreased by 20
int findRightLine(const Mat& rightSide) {
	int nRow = rightSide.rows;  // y-axis

	int leftOfLine = 0, rightOfLine = 0;

	//start at bottom left
	for (int y = nRow;y > 360;y -= 20) {
		for (int x = 530;x < 640;x++) {
			if (rightSide.at<uchar>(Point(x, y)) == 255) {
				if (leftOfLine == 0) {
					leftOfLine = x;
					continue;
				}
				else if (rightOfLine == 0) {
					if ((rightOfLine - leftOfLine) < 12)
						continue;
					else {
						rightOfLine = x;
						break;
					}
				}


			}

		}
		leftOfLine = 0;
		rightOfLine = 0;
	}
	return (leftOfLine + rightOfLine) / 2;
}


/*
int histogramPeakLeft(const Mat& leftSide) {
	int max = 0, temp = 0;
	int maxIntensityX =0 ;
	int nRow = leftSide.rows;  // y-axis
	int nCol = leftSide.cols;  // x-axis

	for (int x = 0;x < nCol / 2;x++) {
		for (int y = 0;y < nRow;y++) {
			temp += leftSide.at<uchar>(Point(x, y));

		}
		if (temp > max) {
			max = temp;
			maxIntensityX = x;
		}
		temp = 0;
	}

	return maxIntensityX;
}



int histogramPeakRight(const Mat& rightSide) {
	int max = 0, temp = 0;
	int maxIntensityX =0;
	int nRow = rightSide.rows;  // y-axis
	int nCol = rightSide.cols;  // x-axis

	//start from the middle of the image
	for (int x = 320;x < nCol;x++) {
		for (int y = 0;y < nRow;y++) {
			temp += rightSide.at<uchar>(Point(x, y));

		}
		if (temp > max) {
			max = temp;
			maxIntensityX = x;
		}
		temp = 0;
	}

	return maxIntensityX;
}

*/
