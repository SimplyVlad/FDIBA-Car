#include "Image.h"



Image::Image(cv::Mat im) : image(im) {

}

void Image::applyGaussianBlur(Image& dst) {
	cv::GaussianBlur(image, dst.image, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
}

void Image::applyHistogramEqualizer(Image& dst) {
	cv::equalizeHist(image, dst.image);

}

void Image::applyThreshold( Image& dst, int thresh, int maxValue) {
	cv::threshold(image, dst.image, thresh, maxValue,cv::THRESH_BINARY);

}

void Image::getBirdsView(cv::Point2f *p1, cv::Point2f *p2, Image& dst) {
	cv::Mat warpMatrix = getPerspectiveTransform(p1, p2);

	warpPerspective(image, dst.image, warpMatrix, dst.image.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);

}

void Image::show(std::string s) {
	cv::imshow(s, image);
}

void Image::showHistogram() {
	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;
	cv::Mat b_hist;

	/// Compute the histograms:
	calcHist(&image, 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);


	// Draw the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());


	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);

	}

	/// Display
	cv::namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

}