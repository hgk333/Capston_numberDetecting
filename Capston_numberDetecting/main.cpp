//
//  main.cpp
//  Capston_numberDetecting
//
//  Created by Tony Kwon on 2015. 11. 18..
//  Copyright © 2015년 Tony Kwon. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "findNumber.hpp"

using namespace std;
using namespace cv;

vector <ContourData> contourData;

int main(){
    
    //car number file open
    IplImage *srcImage;
    
    if ((srcImage = cvLoadImage("/Users/Tony/Documents/workspace_Xcode/Capston_numberDetecting/Capston_numberDetecting/d7217.jpg", CV_LOAD_IMAGE_GRAYSCALE)) == NULL){
        cout<<"picture open Error\n";
        return -1;
    }else
        cout<<"picture open Success\n";
    
//    //show the Resize Image
//    cvNamedWindow("srcImage", CV_WINDOW_AUTOSIZE);
//    cvShowImage("srcImage", srcImage);

    // resize srcImage
    IplImage* resizeSrcImage = cvCreateImage(CvSize(cvGetSize(srcImage).width/2,cvGetSize(srcImage).height/2), IPL_DEPTH_8U, 1);
    cvResize(srcImage, resizeSrcImage);
    
    //get free to srcImage
    cvReleaseImage(&srcImage);
    
//    //show the Resize Image
//    cvNamedWindow("resizeSrcImage", CV_WINDOW_AUTOSIZE);
//    cvShowImage("resizeSrcImage", resizeSrcImage);

    // resize srcImage
    IplImage* thresholdImage = cvCreateImage(cvGetSize(resizeSrcImage), IPL_DEPTH_8U, 1);
    cvResize(resizeSrcImage, thresholdImage);
    IplImage* thresholdImage2 = cvCreateImage(cvGetSize(resizeSrcImage), IPL_DEPTH_8U, 1);
    cvResize(resizeSrcImage, thresholdImage2);
    
    //get free to resizeSrcImage
    cvReleaseImage(&resizeSrcImage);
    
    //threshold
    cvThreshold(thresholdImage, thresholdImage, 150, 255, CV_THRESH_BINARY);
    cvThreshold(thresholdImage2, thresholdImage2, 150, 255, CV_THRESH_BINARY);

//    //show the contoure Image
//    cvNamedWindow("thresholdImage", CV_WINDOW_AUTOSIZE);
//    cvShowImage("thresholdImage", thresholdImage);
    
    // check the picture
    IplImage *contourPicture = cvCreateImage(cvGetSize(thresholdImage), IPL_DEPTH_8U, 3), *getnumberPicture = cvCreateImage(cvGetSize(thresholdImage), IPL_DEPTH_8U, 1);
    
    //to show the contour, change the color of picture to simple
    cvCvtColor(thresholdImage, contourPicture, CV_GRAY2BGR);
  
    // rotation check
    double angle = rotationTest(thresholdImage, contourPicture, contourData) + 180;
//    cout<<"angle = "<<angle<< endl;
    if ( angle != 180 ){
        rotateImage(thresholdImage2, thresholdImage2, angle); // if need to rotate, rotate the picture
    }
    
    //free thresholdImage
    cvReleaseImage(&thresholdImage);
    
    //to show the contour, change the color of picture to simple
    cvCvtColor(thresholdImage2, contourPicture, CV_GRAY2BGR);
    
    //threshold
    cvThreshold(thresholdImage2, getnumberPicture, 120, 255, CV_THRESH_BINARY);
    
    //until now, check the lotation
    // now check the area for nubmer
    cout<< "number is ";
    findNumberArea(thresholdImage2, contourPicture, getnumberPicture, contourData);
    cout<< endl;
    //show the threshold Image
//    cvNamedWindow("thresholdImage2", CV_WINDOW_AUTOSIZE);
//    cvShowImage("thresholdImage2", thresholdImage2);
    
    //show the contoure Image
    cvNamedWindow("contour Image", CV_WINDOW_AUTOSIZE);
    cvShowImage("contour Image", contourPicture);
    
    
    //show the rectangle Image
    cvNamedWindow("getnumberPicture", CV_WINDOW_AUTOSIZE);
    cvShowImage("getnumberPicture", getnumberPicture);
    
    //free all of memory
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&thresholdImage2);
    cvReleaseImage(&contourPicture);
    cvReleaseImage(&getnumberPicture);
    
    return 0;
}