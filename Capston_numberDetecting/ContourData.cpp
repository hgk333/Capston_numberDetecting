//
//  ContourData.cpp
//  Capston_numberDetecting
//
//  Created by Tony Kwon on 2015. 11. 24..
//  Copyright © 2015년 Tony Kwon. All rights reserved.
//

#include "ContourData.hpp"
int ContourData::getHeight(){
    return height;
};
int ContourData::getMaxX(){
    return maxX;
}
int ContourData::getMaxY(){
    return maxY;
}
int ContourData::getMinX(){
    return minX;
}
int ContourData::getMinY(){
    return minY;
}
int ContourData::getWidth(){
    return width;
}
int ContourData::getCenterX(){
    return centerX;
}
int ContourData::getCenterY(){
    return centerY;
}
void ContourData::setHeight(int input){
    height = input;
}
void ContourData::setMaxX(int input){
    maxX = input;
}
void ContourData::setMaxY(int input){
    maxY = input;
}
void ContourData::setMinX(int input){
    minX = input;
}
void ContourData::setMinY(int input){
    minY = input;
}
void ContourData::setWidth(int input){
    width = input;
}
void ContourData::setCenter(){
    centerX = (maxX + minX) / 2;
    centerY = (maxY + minY) / 2;
}
