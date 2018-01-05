#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace std;

using namespace cv;


int main() {
	/*
	vector<Point> srcCoordinates;
	srcCoordinates.push_back(Point(, 69));
	srcCoordinates.push_back(Point(72, 2186));
	srcCoordinates.push_back(Point(1584, 2426));
	srcCoordinates.push_back(Point(1912, 291));


	cv::Point2f src_vertices[4];
	src_vertices[0] = srcCoordinates[0];
	src_vertices[1] = srcCoordinates[1];
	src_vertices[2] = srcCoordinates[2];
	src_vertices[3] = srcCoordinates[3];
	
	*/
	  
	

	 
	 
	// Read image
	
	Mat src = imread("test_images\\test2\\Test22.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	 
	 

	  
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	// Set threshold and maxValue
	double thresh = 160;
	double maxValue = 255;
	equalizeHist(src, src);

	 
	 
	 

		// Binary Threshold
	threshold(src, dst, thresh, maxValue, THRESH_BINARY);
 
	namedWindow("gg", WINDOW_AUTOSIZE);
	namedWindow("bb", WINDOW_AUTOSIZE);
	imshow("bb", dst);
	Mat roi = dst(Rect(250, 450, 980, 270));
	imshow("gg", roi);
	 
	waitKey(0);  
	return 0;
}

