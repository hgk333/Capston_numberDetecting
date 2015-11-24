//
//  ContourData.hpp
//  Capston_numberDetecting
//
//  Created by Tony Kwon on 2015. 11. 24..
//  Copyright © 2015년 Tony Kwon. All rights reserved.
//

#ifndef ContourData_hpp
#define ContourData_hpp

#include <stdio.h>

class ContourData{
    private :
    int maxX;
    int maxY;
    int minX;
    int minY;
    int width;
    int height;
    int centerX;
    int centerY;
    public :
    int getMaxX();
    int getMaxY();
    int getMinX();
    int getMinY();
    int getWidth();
    int getHeight();
    int getCenterX();
    int getCenterY();
    void setMaxX(int input);
    void setMaxY(int input);
    void setMinX(int input);
    void setMinY(int input);
    void setWidth(int input);
    void setHeight(int input);
    void setCenter();
    
};

#endif /* ContourData_hpp */
