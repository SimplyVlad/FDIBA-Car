# FDIBA-Car

Steps for lane line finding

1) Compute the camera calibration matrix and distortion coefficients using frames of chessboard captured by the camera.
2) Apply a distortion correction to raw images.
3) Reduce noise, use hologram equalizer and create a thresholded binary image.
4) Apply a perspective transform to rectify binary image ("birds-eye view").
5) Detect lane pixels and fit to find the lane boundary.
6) Determine the curvature of the lane and vehicle position with respect to center.
7) Warp the detected lane boundaries back onto the original image.
8) Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

---------------------------------------------------------------------------
 
1) specify the chessboard width and height, and number of chessboard frames. The output file contains camera matrix and distortion 
coefficients. Use them in camera_calibrate/undistort.cpp to calibrate test images
 
3)thresholdBinary.cpp - Reduce noise, use hologram equalizer and create a thresholded binary image. Set region of interest

Explanation is comming soon.. 