//
//  findNumber.cpp
//  Capston_numberDetecting
//
//  Created by Tony Kwon on 2015. 11. 23..
//  Copyright © 2015년 Tony Kwon. All rights reserved.
//

#include "findNumber.hpp"

void printNumberByMat(IplImage* getNumberPicture, vector<ContourData> contourData){
    CvMat *srcMat, matHeader;
    for (int i = 0; i < contourData.size(); i++) {
        cvSetImageROI(getNumberPicture, cvRect(contourData[i].getMinX(), contourData[i].getMinY(), contourData[i].getWidth(), contourData[i].getHeight()));
        srcMat = cvGetMat(getNumberPicture, &matHeader);
        PrintMat(srcMat, "srcMat");
    }
}

void findNumberArea(IplImage* thresholdImage2, IplImage* contourPicture, IplImage* getnumberPicture, vector<ContourData> contourData){
    contourData.clear();
    
    // create storate for contour
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq *first_contour = 0;
    
    //decide a interesting area (center)
    int imageMinX = cvGetSize(thresholdImage2).width/4 , imageMaxX = cvGetSize(thresholdImage2).width - imageMinX, imageMinY = cvGetSize(thresholdImage2).height/4, imageMaxY = cvGetSize(thresholdImage2).height - imageMinY;
    
    //find the contour
    int nContour = cvFindContours(thresholdImage2, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
//    cout<<"nContour = "<< nContour<< "\n";
    
    CvSeq *contour; //for saving the contour
    
    int highestHeight = 0;
    
    for (contour = first_contour ; contour != 0 ; contour = contour->h_next) {
        int tmp_maxX = 0 , tmp_maxY = 0 , tmp_minX = 1000000, tmp_minY = 1000000, tmp_width = 0, tmp_height = 0;
        
        // Draw the contour
        cvDrawContours(contourPicture, contour, CV_RGB(0,0,255), CV_RGB(255, 0, 0), 2, 1);
        
        //draw the rectangle on the picture outside of contour
        for (int i = 0 ; i < contour->total ; i++) {
            // find the area of contour
            CvPoint* ContourPoint = (CvPoint*)cvGetSeqElem(contour, i);
            if (tmp_maxX < ContourPoint->x)
                tmp_maxX = ContourPoint->x;
            if (tmp_maxY < ContourPoint->y)
                tmp_maxY = ContourPoint->y;
            if (tmp_minX > ContourPoint->x)
                tmp_minX = ContourPoint->x;
            if (tmp_minY > ContourPoint->y)
                tmp_minY = ContourPoint->y;
        }
        //calculate width and height
        tmp_width = tmp_maxX - tmp_minX; tmp_height = tmp_maxY - tmp_minY;
        
        //if rate of fiture is right, input data in vector
        if((double)tmp_width/(double)tmp_height < 1 && tmp_height > 10 && tmp_maxX < imageMaxX && tmp_minX > imageMinX && tmp_minY > imageMinY && tmp_maxY < imageMaxY ){
            //check the highest height
            if (highestHeight < tmp_height) {
                highestHeight = tmp_height;
            }
            
//            cvRectangle(contourPicture, CvPoint(tmp_maxX,tmp_maxY), CvPoint(tmp_minX,tmp_minY), CV_RGB(0, 255, 0));
            ContourData tmp_contour;
            tmp_contour.setMaxX(tmp_maxX); tmp_contour.setMaxY(tmp_maxY); tmp_contour.setMinX(tmp_minX); tmp_contour.setMinY(tmp_minY); tmp_contour.setHeight(tmp_height); tmp_contour.setWidth(tmp_width);
            tmp_contour.setCenter();
            contourData.push_back(tmp_contour);
            
            //confirm the value stored at vector
            //            cout<<"max ( "<<tmp_maxX<<","<<tmp_maxY<<")\n";
            //            cout<<"min ( "<<tmp_minX<<","<<tmp_minY<<")\n";
            //            cout<<"width : "<<tmp_width<< " height : "<<tmp_height<<"\n";
        }
    }
    throwoutArea(contourData, contourPicture, highestHeight/3*2);
    //find the number area.
    cvReleaseMemStorage(&storage);
    
    printNumberByMat(getnumberPicture, contourData);
    
}
double rotationTest(IplImage *thresholdImage, IplImage* contourPicture, vector<ContourData> contourData){
    int returnValue = 0;
    
    // create storate for contour
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq *first_contour = 0;
    
    //decide a interesting area (center)
    int imageMinX = cvGetSize(thresholdImage).width/4 , imageMaxX = cvGetSize(thresholdImage).width - imageMinX, imageMinY = cvGetSize(thresholdImage).height/4, imageMaxY = cvGetSize(thresholdImage).height - imageMinY;
    
    //find the contour
    int nContour = cvFindContours(thresholdImage, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
//    cout<<"nContour = "<< nContour<< "\n";
    
    CvSeq *contour; //for saving the contour
    
    for (contour = first_contour ; contour != 0 ; contour = contour->h_next) {
        int tmp_maxX = 0 , tmp_maxY = 0 , tmp_minX = 1000000, tmp_minY = 1000000, tmp_width = 0, tmp_height = 0;
        
        // Draw the contour
        cvDrawContours(contourPicture, contour, CV_RGB(0,0,255), CV_RGB(255, 0, 0), 2, 1);
        
        //draw the rectangle on the picture outside of contour
        for (int i = 0 ; i < contour->total ; i++) {
            // find the area of contour
            CvPoint* ContourPoint = (CvPoint*)cvGetSeqElem(contour, i);
            if (tmp_maxX < ContourPoint->x)
                tmp_maxX = ContourPoint->x;
            if (tmp_maxY < ContourPoint->y)
                tmp_maxY = ContourPoint->y;
            if (tmp_minX > ContourPoint->x)
                tmp_minX = ContourPoint->x;
            if (tmp_minY > ContourPoint->y)
                tmp_minY = ContourPoint->y;
        }
        //calculate width and height
        tmp_width = tmp_maxX - tmp_minX; tmp_height = tmp_maxY - tmp_minY;
        
        //if rate of fiture is right, input data in vector
        if((double)tmp_width/(double)tmp_height < 1 && tmp_height > 20 && tmp_maxX < imageMaxX && tmp_minX > imageMinX && tmp_minY > imageMinY && tmp_maxY < imageMaxY ){
        
            //cvRectangle(contourPicture, CvPoint(tmp_maxX,tmp_maxY), CvPoint(tmp_minX,tmp_minY), CV_RGB(0, 255, 0));
            ContourData tmp_contour;
            tmp_contour.setMaxX(tmp_maxX); tmp_contour.setMaxY(tmp_maxY); tmp_contour.setMinX(tmp_minX); tmp_contour.setMinY(tmp_minY); tmp_contour.setHeight(tmp_height); tmp_contour.setWidth(tmp_width);
            tmp_contour.setCenter();
            contourData.push_back(tmp_contour);
            
            //confirm the value stored at vector
            //            cout<<"max ( "<<tmp_maxX<<","<<tmp_maxY<<")\n";
            //            cout<<"min ( "<<tmp_minX<<","<<tmp_minY<<")\n";
            //            cout<<"width : "<<tmp_width<< " height : "<<tmp_height<<"\n";
        }
    }
    returnValue = arrangeContourData(contourData, contourPicture);
        
    //find the number area.
    cvReleaseMemStorage(&storage);
    
    return returnValue;
}


double arrangeContourData(std::vector<ContourData> &contourData, IplImage* contourPicture){
    int rotateCheck = 0;
    
    for (int i = 0; i < contourData.size() ; i++) {
        for (int j = 0; j < contourData.size() - 1; j++) {
            if (contourData[j].getMinX() > contourData[j+1].getMinX()) {
                swap(contourData[j], contourData[j+1]);
            }
        }
    }
    
    for (int i = 0; i < contourData.size(); i++) {
        //check rotation
        if (i < contourData.size() - 1 && contourData[i].getCenterY() < contourData[i+1].getCenterY() ) {
            if (contourData[i].getHeight() - 5 < contourData[i+1].getHeight() && contourData[i].getHeight() + 5 > contourData[i+1].getHeight()) { // compare to similar things
                rotateCheck ++ ;
            }
        }
        
//        //print information
//        cout<<"min ( "<<contourData[i].getMinX()<<","<<contourData[i].getMinY()<<" )\n";
//        cout<<"max ( "<<contourData[i].getMaxX()<<","<<contourData[i].getMaxY()<<" )\n";
//        cout<<"center ( "<<contourData[i].getCenterX()<<","<<contourData[i].getCenterY()<<" )\n";
//        cout<<"width : "<<contourData[i].getWidth()<< " height : "<<contourData[i].getHeight()<<"\n"<<endl;
//        cvRectangle(contourPicture, cvPoint(contourData[i].getMaxX(), contourData[i].getMaxY()), cvPoint(contourData[i].getMinX(), contourData[i].getMinY()), CV_RGB(0, 255, 0));
    }
    
    if (rotateCheck > 4) {
        return atan2((double) contourData[0].getMaxY() - (double) contourData[contourData.size()-1].getMaxY(), (double)contourData[0].getMaxX() - (double)contourData[contourData.size()-1].getMaxX()) * 180 / 3.141592f ;
    }
    
    return 0;
}

void throwoutArea(std::vector<ContourData> &contourData, IplImage* contourPicture, int highestHeight){
    
    // delete area by rate and height
    for (int i = 0; i < contourData.size(); i ++) {
        if (contourData[i].getHeight() < highestHeight || (double)contourData[i].getWidth()/(double)contourData[i].getHeight() < 0.35 || (double)contourData[i].getWidth()/(double)contourData[i].getHeight() > 0.70 ) {
            contourData.erase(contourData.begin() + i);
            i--;
        }
    }
    
    // delete inner contour or charactor
    if (contourData.size() > 6) {
        //sort by height
        for (int i = 0; i < contourData.size() ; i++) {
            for (int j = 0; j < contourData.size() - 1; j++) {
                if (contourData[j].getHeight() < contourData[j+1].getHeight()) {
                    swap(contourData[j], contourData[j+1]);
                }
            }
        }
        //delete short height
        while (contourData.size() != 6) {
            contourData.pop_back();
        }
    }
    //sorting by x position
    for (int i = 0; i < contourData.size() ; i++) {
        for (int j = 0; j < contourData.size() - 1; j++) {
            if (contourData[j].getMinX() > contourData[j+1].getMinX()) {
                swap(contourData[j], contourData[j+1]);
            }
        }
    }
    
//    //print information
//    for (int i = 0; i < contourData.size(); i++) {
//        cout<<"min ( "<<contourData[i].getMinX()<<","<<contourData[i].getMinY()<<" )\n";
//        cout<<"max ( "<<contourData[i].getMaxX()<<","<<contourData[i].getMaxY()<<" )\n";
//        cout<<"center ( "<<contourData[i].getCenterX()<<","<<contourData[i].getCenterY()<<" )\n";
//        cout<<"width : "<<contourData[i].getWidth()<< " height : "<<contourData[i].getHeight()<<"\n"<<endl;
//        cvRectangle(contourPicture, cvPoint(contourData[i].getMaxX(), contourData[i].getMaxY()), cvPoint(contourData[i].getMinX(), contourData[i].getMinY()), CV_RGB(0, 255, 0));
//    }
}

void rotateImage(const IplImage* src, IplImage* dst, double degree)
{
    // Only 1-Channel
    if(src->nChannels != 1)
        return;
    
    CvPoint2D32f    centralPoint    = cvPoint2D32f(src->width/2, src->height/2);            // 회전 기준점 설정(이미지의 중심점)
    CvMat*            rotationMatrix    = cvCreateMat(2, 3, CV_32FC1);                        // 회전 기준 행렬
    
    // Rotation 기준 행렬 연산 및 저장(90도에서 기울어진 각도를 빼야 본래이미지(필요시 수정))
    cv2DRotationMatrix(centralPoint, degree, 1, rotationMatrix);
    
    // Image Rotation
    cvWarpAffine(src, dst, rotationMatrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
    
    // Memory 해제
    cvReleaseMat(&rotationMatrix);
}

int PrintMat(const CvMat *mat, const char *strName)
{
    double   fValue;
    double total[CHECKSIZE][CHECKSIZE] = { 0 };
    double zero[CHECKSIZE][CHECKSIZE] = { 0 };
    int area_x = mat->cols / CHECKSIZE;
    int area_y = mat->rows / CHECKSIZE;
    //printf(" %s  \n =  \n", strName);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            fValue = cvGetReal2D(mat, i, j);
//            printf("%3d", cvRound(fValue));
        }
//        printf("\n");
    }
    for (int i = 0; i < CHECKSIZE; i++){
        for (int j = 0; j < CHECKSIZE; j++){
            for (int y = area_y*i; y < area_y*(i + 1); y++)
            {
                for (int x = area_x*j; x < area_x*(j + 1); x++)
                {
                    fValue = cvGetReal2D(mat, y, x);
                    if (cvRound(fValue) == 0)
                        zero[i][j] += 1;
                    total[i][j] += 1;
                }
            }
            total[i][j] = zero[i][j] / total[i][j];
        }
    }
    show_zeroArea(total);
    cout<<counting(total);
    
    return 0;

}
void show_zeroArea(double result[CHECKSIZE][CHECKSIZE]){
    for (int i=0;i< CHECKSIZE;i++   )
        for (int j=0; j<CHECKSIZE; j++) {
//            printf("rate[%d][%d] = %lf \n",i,j,result[i][j]);
        }
}

int counting(double result[CHECKSIZE][CHECKSIZE]){
    int numbertest;
    int num[9]={0};
    int number;
    for(int i=0;i<CHECKSIZE;i++){
        for(int j=0;j<CHECKSIZE;j++){
            if(result[i][j]<=0.2) numbertest = 1;
            else if(result[i][j]<=0.4 &&result[i][j]>0.2) numbertest = 2;
            else if(result[i][j]<=0.6 &&result[i][j]>0.4) numbertest = 3;
            else if(result[i][j]<=0.8 &&result[i][j]>0.6) numbertest = 4;
            else numbertest = 5;
            num[3*i+j]= numbertest;
            numbertest=1;
            
        }
    }
    
    if(num[0]==3&&num[1]==2&&num[2]==3&&num[3]==4&&num[4]==1&&num[5]==4&&(num[6]==3||num[6]==4)&&num[7]==2&&(num[8]==3||num[8]==4)){
        number = 0;
    }
    else if((num[0]==2||num[0]==3)&&(num[1]==2||num[1]==3)&&num[2]==5&&num[3]==1&&num[4]==1&&(num[5]==4||num[5]==5)&&num[6]==1&&num[7]==1&&(num[8]==4||num[8]==5)){
        number = 1;
    }
    else if(num[0]==3&&(num[1]==2||num[1]==3)&&(num[2]==3||num[2]==4)&&num[3]==1&&(num[4]==1||num[4]==2||num[4]==3)&&(num[5]==2||num[5]==3||num[4])&&(num[6]==2||num[6]==3)&&(num[7]==4||num[7]==5)&&num[8]==2){
        number = 2;
    }
    else if(num[0]==2&&num[1]==3&&(num[2]==3||num[2]==4)&&num[3]==1&&(num[4]==2||num[4]==3)&&(num[5]==3||num[5]==4)&&(num[6]==3||num[6]==4)&&(num[7]==2||num[7]==3)&&num[8]==4){
        number = 3;
    }
    else if(num[0]==1&&(num[1]==1||num[1]==2||num[1]==3)&&(num[2]==3||num[2]==4||num[2]==5)&&(num[3]==1||num[3]==2)&&(num[4]==2||num[4]==3)&&(num[5]==3||num[5]==4)&&(num[6]==2||num[6]==3)&&(num[7]==2||num[7]==3)&&(num[8]==4||num[8]==5)){
        number = 4;
    }
    else if((num[0]==3||num[0]==4)&&(num[1]==3||num[1]==4)&&(num[2]==2||num[2]==3)&&(num[3]==3||num[3]==4)&&(num[4]==2||num[4]==3)&&(num[5]==3||num[5]==4)&&num[6]==3&&(num[7]==2||num[7]==3)&&(num[8]==3||num[8]==4)){
        number = 5;
    }
    else if(num[0]==1&&(num[1]==3||num[1]==4)&&num[2]==1&&(num[3]==3||num[3]==4)&&(num[4]==3||num[4]==4)&&num[5]==3&&(num[6]==3||num[6]==4)&&(num[7]==2||num[7]==3)&&(num[8]==3||num[8]==4)){
        number = 6;
    }
    
    else if((num[0]==3||num[0]==4)&&num[1]==2&&num[2]==4&&num[3]==1&&num[4]==2&&(num[5]==2||num[5]==3)&&num[6]==1&&(num[7]==3||num[7]==4)&&num[8]==1){
        number = 7;
    }
    else if((num[0]==2||num[0]==3)&&(num[1]==2||num[1]==3)&&(num[2]==3||num[2]==4)&&(num[3]==4||num[3]==3)&&(num[4]==2||num[4]==3||num[4]==4)&&(num[5]==3||num[5]==4||num[5]==5)&&(num[6]==3||num[6]==4)&&(num[7]==2||num[7]==3)&&num[8]==4){
        number = 8;
    }
    else if(num[0]==3&&num[1]==2&&(num[2]==3||num[2]==4)&&num[3]==3&&num[4]==3&&num[5]==4&&num[6]==1&&num[7]==4&&num[8]==1){
        number = 9;
    }
    
    
    return number;
}