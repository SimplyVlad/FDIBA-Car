#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Image.h"

using namespace cv;


int main() {

	Image src(imread("camera.jpg", IMREAD_GRAYSCALE));
	Image dst;
	 
//	src.applyGaussianBlur(dst);
	
	

	src.applyHistogramEqualizer(src);
	 
	src.applyThreshold(dst, 190, 255);
	

	return 0;
	 
}