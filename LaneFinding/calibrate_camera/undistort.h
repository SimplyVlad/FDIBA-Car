#pragma once


#include <opencv2/core/core.hpp>

class UndistortImages {
private:
	// Camera parameters
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
	std::vector<std::string> inputImagesPaths;

public:
	void readCameraParameters(char*);
	void loadImages(char*);
	void undistortImages();
};