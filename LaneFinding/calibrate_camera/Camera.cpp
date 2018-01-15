#include "Camera.h"



const char *Camera::usage=
" \nexample command line for calibration from a live feed.\n"
"   calibration  -w 4 -h 5 -s 0.025 -o camera.yml -op -oe\n"
" \n"
" example command line for calibration from a list of stored images:\n"
"   imagelist_creator image_list.xml *.png\n"
"   calibration -w 4 -h 5 -s 0.025 -o camera.yml -op -oe image_list.xml\n"
" where image_list.xml is the standard OpenCV XML/YAML\n"
" use imagelist_creator to create the xml or yaml list\n"
" file consisting of the list of strings, e.g.:\n"
" \n"
"<?xml version=\"1.0\"?>\n"
"<opencv_storage>\n"
"<images>\n"
"view000.png\n"
"view001.png\n"
"<!-- view002.png -->\n"
"view003.png\n"
"view010.png\n"
"one_extra_view.jpg\n"
"</images>\n"
"</opencv_storage>\n";


const char* Camera::liveCaptureHelp = "When the live video from camera is used as input, the following hot-keys may be used:\n"
		"  <ESC>, 'q' - quit the program\n"
		"  'g' - start capturing images\n"
	"  'u' - switch undistortion on/off\n";