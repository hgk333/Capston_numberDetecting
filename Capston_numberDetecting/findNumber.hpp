//
//  findNumber.hpp
//  Capston_numberDetecting
//
//  Created by Tony Kwon on 2015. 11. 23..
//  Copyright © 2015년 Tony Kwon. All rights reserved.
//

#ifndef findNumber_hpp
#define findNumber_hpp

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "ContourData.hpp"

#define CHECKSIZE 3

using namespace std;


bool arrangeContourData(std::vector<ContourData> &contourData, IplImage* contourPicture);
int PrintMat(const CvMat *mat, const char *strName);
void show_zeroArea(double result[CHECKSIZE][CHECKSIZE]);
int counting(double result[CHECKSIZE][CHECKSIZE]);
void rotateImage(const IplImage* src, IplImage* dst, double degree);
bool rotationTest(IplImage *thresholdImage, IplImage* contourPicture, vector<ContourData> contourData);
void findNumberArea(IplImage* thresholdImage2, IplImage* contourPicture, IplImage* getnumberPicture, vector<ContourData> contourData);
void throwoutArea(std::vector<ContourData> &contourData, IplImage* contourPicture, int highestHeight);
void printNumberByMat(IplImage* thresholdImage2, vector<ContourData> contourData);

/*
double number_info[10][CHECKSIZE][CHECKSIZE]={
    {
        {0.5, 0.5 0.68}
        {
    }
}*/


#endif /* findNumber_hpp */
