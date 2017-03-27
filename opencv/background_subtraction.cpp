#define _USE_MATH_DEFINES
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

string win_src = "src";
string win_back = "background";
string output_image = "circledetect";
string win_diff = "diff";

Mat src;
Mat dst;
Mat src_gray;
Mat src_binary;
Mat src_md;
Mat src_mask;
Mat canny_output;
Mat background;
Mat back_gray;

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
//        for (int counter = 0 ; counter < 60 ; counter++) {
            /// Load source capture and convert it to gray
            capture >> src;
            /// Create Window
            namedWindow (win_back, CV_WINDOW_AUTOSIZE);
            namedWindow (output_image, CV_WINDOW_AUTOSIZE);
            namedWindow (win_src, CV_WINDOW_AUTOSIZE);
            namedWindow (win_diff, CV_WINDOW_AUTOSIZE);

            /// Convert image to gray and blur it
            cvtColor( src, src_gray, CV_BGR2GRAY );
            cvtColor( background, back_gray, CV_BGR2GRAY );
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
            findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
            /// Define contours
            dst = Mat::zeros( canny_output.size(), CV_8UC3 );
            //Find marker
            //Define Values
            int m_numAllMarker = 0;
            Point2f center;
            float radius;
            float m_areaRatio = 1.0;
            int NUM_MARKER =2;
            for (int i = 0; i< contours.size();i++) {
                minEnclosingCircle(contours[i], center, radius);
                float area = contourArea(Mat(contours[i]));
                float perimeter = arcLength(Mat(contours[i]),true);
                float roundness = 4 * M_PI * area / perimeter / perimeter;
                float averagediameter = perimeter / M_PI;
                    /// New marker found
                    if (area < m_areaRatio*radius*radius*M_PI && roundness > 0.6 && area > 70) {
                        if (area > 1200) {
                            cout << "Warning :Too close" << endl;
                        } else {
                            /// Draw Contours
                            drawContours( dst, contours, i, color, 1, 8, hierarchy, 0, Point() );
                            /// Output
                            cout << "roundness :" << roundness 
                            << "     perimeter :" << perimeter 
                            << "     area :" << area 
                            << "     average diameter :" << averagediameter 
                            << "     center : " << center 
                            << "     radius : " << radius << endl;
                            if (m_numAllMarker == NUM_MARKER) break;
                        }
                    }
            }

            /// Show caputre
            imshow(win_back, background);
            imshow(win_src, src);
            imshow(win_diff, src_gray);
            imshow(output_image, dst);

            if (waitKey(1) == 'q') break;
        }
//	}
	return 0;
}
