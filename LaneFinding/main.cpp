#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Image.h"
#include <iostream> 
#include <vector>
#include "polyfit.hpp"

using namespace cv;


int findLeftLineCenter(std::vector<int>& v) {
	int max = 0,x=0;
	for (int i = 0;i < 320;i++) {
		if (v[i] > max) {
			max = v[i];
			x = i;
		}
	}
	return x;
}

int findRightLineCenter(std::vector<int>& v) {
	int max = 0, x = 320;
	for (int i = 320;i < 640;i++) {
		if (v[i] > max) {
			max = v[i];
			x = i;
		}
	}
	return x;
}
 
int main() {
	 
	 
	Image src(imread("camera.jpg", IMREAD_GRAYSCALE));
	Image dst;
	 
//	src.applyGaussianBlur(dst);
	
	

	src.applyHistogramEqualizer(dst);
	 
	//src.applyThreshold(dst, 190, 255);
	
 
	int bottom_leftx = 110;
	int bottom_lefty = 480;

	int upper_leftx = 260;
	int upper_lefty = 120;

	int upper_rightx = 410;
	int upper_righty = 120;

	int bottom_rightx = 560;
	int bottom_righty = 480;


	cv::Point2f src_vertices[4];
	src_vertices[0] = Point(bottom_leftx, bottom_lefty);
	src_vertices[1] = Point(upper_leftx, upper_lefty);
	src_vertices[2] = Point(upper_rightx, upper_righty);
	src_vertices[3] = Point(bottom_rightx, bottom_righty);
	

	Point2f dst_vertices[4];
	dst_vertices[0] = Point(0, 480);
	dst_vertices[1] = Point(0, 0);
	dst_vertices[2] = Point(640, 0);
	dst_vertices[3] = Point(640, 480);

 
	Image dst1;
	 
	dst.getBirdsView(src_vertices, dst_vertices, dst1);

	dst1.applyThreshold(dst1, 190, 255);
	 
	imshow("src", dst1.getIm());
	 
	waitKey();
	return 0;
}






