#include "undistort.h"

#include "Camera.h"
 

#include <iostream>
#include <cstdlib>

	using namespace cv;
	using namespace std;

	void printHelp(char* programName) {
		cout << " Correct usage: " << programName << " camera.yml" << " images_paths.xml " << endl;
		cout << " camera.yml = file with camera matrix and distortion coefficients. " << endl;
		cout << " images_paths.xml = file with path to images that should be undistorted." << endl;
		exit(EXIT_FAILURE);
	}

	
	int main(int argc, char** argv) {
		
		Camera::cameraCalibrate(argc, argv);

		//create delay so it can evaluate the camera matrix
		waitKey(5000);


		UndistortImages undistortImages;
		undistortImages.readCameraParameters("D:\\C++ projects\\Opencv\\OpenCV\\x64\\Debug\\personal_camera.yml");
		undistortImages.loadImages("Images.xml");
		undistortImages.undistortImages();

		return 0;
	}

