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
 
1) Run the LaneFinding.exe file from Debug with parameters chessboard width and height, and number of chessboard frames (for example, -w 9 -h 5 -n 14). The output file(also in Debug folder) contains camera matrix and distortion coefficients. Use them in later in calibrateAndUndistort.cpp to calibrate an image. NOTE: Camera calibration should be done before the other part of the project
 
3) Blur the image by applying Gaussian function to reduce noise and detail. Apply hologram equalizer to improve the contrast in the image and make the lines more reocognizable. Then apply binary threshold - that is, the image is gray, so its pixel values are from 0 to 255. After applying the threshold all pixels which values are greater than lets say 170 (thresh) become 255(maxValue). In that way the image contains only 1 and 0's, or in other words, lines and black.   

![alt text](https://user-images.githubusercontent.com/20464575/34950126-e8318ae4-fa1a-11e7-9d28-9f7aefb430f9.jpg)

![alt text](https://user-images.githubusercontent.com/20464575/34950014-857ba998-fa1a-11e7-9a49-129240ce61cb.png) 
 
4) Calculate perspective transform. Get the coordinates of four vertices in the source image(**p1 in getBirdsView**) and four coordinates defining where the previos points will be placed on the destination image(in that case, the points from the source image are mapped to the whole viewport). **warpPerspective** apllies the perspective transformation using the returned matrix. The point of doing this is to specify the region containing only the lane lines in order to get "bird view" of them and easily make some calculations.

![alt text](https://user-images.githubusercontent.com/20464575/35812864-caf374a2-0a9a-11e8-84ef-b9dd165abd8b.png)