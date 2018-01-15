#pragma once


#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"



class Image {
	cv::Mat image;
	

public:
	Image(cv::Mat im = cv::Mat());

	void applyThreshold(Image& dst, int thresh, int maxValue);
	void applyHistogramEqualizer( Image& dst);
	void getBirdsView(cv::Point2f *p1, cv::Point2f *p2, Image& dst);
	void applyGaussianBlur( Image& dst);
	void show(std::string s="window");
	void showHistogram();

};