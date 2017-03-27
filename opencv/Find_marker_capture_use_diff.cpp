#define _USE_MATH_DEFINES
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;
using namespace cv;

string win_src = "src";
string output_image = "circledetect";
string win_back = "background";

Mat src;
Mat dst;
Mat src_gray;
Mat src_binary;
Mat src_md;
Mat src_mask;
Mat canny_output;
Mat back_gray;
Mat background;

// focus
float f = 481.8457;


// Define first thresh
int thresh = 100;

/// Define line color
Scalar color = Scalar( 255,255,255);


/** @function main */
int main( int argc, char** argv )
{
  /// Open source capture
	VideoCapture capture(0);
	if(!capture.isOpened()) {
		cout << "error : can't open camera'" << endl;
		return -1;
	}

    /// background image
    capture >> background;

    while (1){
        /// Load source capture and convert it to gray
    	capture >> src;
        /// Create Window
        namedWindow (output_image, CV_WINDOW_AUTOSIZE);
    	namedWindow (win_src, CV_WINDOW_AUTOSIZE);
        namedWindow (win_back, CV_WINDOW_AUTOSIZE);

        /// Convert image to gray and blur it
        cvtColor( src, src_gray, CV_BGR2GRAY );
        cvtColor( background, back_gray, CV_BGR2GRAY );
        /// diff back and src
        absdiff(src_gray,back_gray,src_gray);
        blur( src_gray, src_gray, Size(3,3) );

        /// thresh
        threshold(src_gray, src_binary, thresh, 255, THRESH_BINARY);
        dilate(src_binary, src_md, Mat(), Point(-1,-1),4);
        erode(src_md, src_mask, Mat(), Point(-1,-1),4);
        bitwise_and(src_binary, src_mask, src_binary);
        bitwise_and(src_gray, src_mask, src_gray);

        /// Define Contours
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        /// Detect edges using canny
        Canny( src_binary, canny_output, thresh, thresh*2, 3 );
        /// Find contours
        findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        /// Define contours
        dst = Mat::zeros( canny_output.size(), CV_8UC3 );
        //Find marker
        //Define Values

       //Define Values
        Point2f center;
        Point2f Camera_Coodinate;
        float radius;
        float m_areaRatio = 1.0;
        for (int i = 0; i< contours.size();i++) {
            minEnclosingCircle(contours[i], center, radius);
            Camera_Coodinate.x = center.x - 320;
            Camera_Coodinate.y = - (center.y - 240);
            float theta = atan2(Camera_Coodinate.x,f);
            float phi = atan2(-Camera_Coodinate.y,f);
            float area = contourArea(Mat(contours[i]));
            float perimeter = arcLength(Mat(contours[i]),true);
            float roundness = 4 * M_PI * area / perimeter / perimeter;
            float distance = f * 5 / radius;
                /// New marker found
                if (area < m_areaRatio*radius*radius*M_PI && roundness > 0.6 && area > 100) {
                    if (area > 1800) {
                        cout << "Warning :Too close" << endl;
                    } else {
                        /// Draw Contours
                        drawContours( dst, contours, i, color, 1, 8, hierarchy, 0, Point() );
                        /// Output
                        cout 
//                        << "roundness : " << roundness 
//                        << "     Camera_Coodinate : " << Camera_Coodinate 
//                        << "     Theta : " << theta 
//                        << "     Phi : " << phi 
//                        << "     diameter : " << radius *2 
//                        << "     distance : " << distance <<"cm"
                        << "     (x,y,z) : ("
                        << distance*sin(theta)*cos(phi) << "," << distance * sin(theta)*sin(phi) << "," << distance * cos(theta)
                        << ")" << endl;
                    }
                }
        }

      /// Show caputre
		imshow(win_src, src);
        imshow(output_image, dst);
        imshow(win_back, background);

		if (waitKey(1) == 'q') break;
	}
	return 0;
}
