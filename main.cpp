//
//  main.cpp
//  Keyboarding Monitoring
//
//  Created by Peng Peng on 2014-11-01.
//  Copyright (c) 2014 彭 彭. All rights reserved.
//

#include <iostream>
//#include <time.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void    HandDetection();
int     LaunchDefCam();
int     LaunchUsbCam();
int     CaptureCam();
string  InttoString(int iInput);


int main(int argc, const char * argv[]) {
    // insert code here...


//    LaunchDefCam();
//    LaunchUsbCam();

//    HandDetection();
    CaptureCam();

    return 0;
}

void HandDetection()
{
//    CvCapture* capture = cvCreateFileCapture("/Users/PengPeng/Downloads/handdetection.avi");
//    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);

    IplImage *img = cvLoadImage("/Users/PengPeng/Downloads/Typing.jpg", CV_LOAD_IMAGE_ANYCOLOR);
//    cvShowImage("image", img);
//    cvWaitKey(0);
//    cvReleaseImage(&img);
//    cvDestroyWindow("image");


    CvSize sz = cvGetSize(img);

    IplImage* src = cvCreateImage( sz, 8, 3 );
    IplImage* hsv_image = cvCreateImage( sz, 8, 3);
    IplImage* hsv_mask = cvCreateImage( sz, 8, 1);

    CvScalar  hsv_min = cvScalar(0, 30, 80, 0);
    CvScalar  hsv_max = cvScalar(20, 150, 255, 0);

    src = img;

    cvNamedWindow( "src",1); cvShowImage( "src", src);

    cvCvtColor(src, hsv_image, CV_BGR2HSV);

    cvNamedWindow( "hsv-img",1); cvShowImage( "hsv-img", hsv_image);

    cvInRangeS (hsv_image, hsv_min, hsv_max, hsv_mask);

    cvNamedWindow( "hsv-msk",1); cvShowImage( "hsv-msk", hsv_mask); hsv_mask->origin = 1;

    cvWaitKey(0);

    cvDestroyAllWindows();


}   // end of HandDetection()

int LaunchDefCam()
{
    VideoCapture vcTest(1);

    if(!vcTest.isOpened()){

        return -1;
    }

    Mat matFrame;

    bool stop = false;
    while(!stop){

        vcTest>>matFrame;

        imshow("CamTest", matFrame);

        if(waitKey(30) >= 0)
            stop = true;
    }

    return 0;

}   // end of LaunchDefCam()

int LaunchUsbCam()
{
    CvCapture *cpCapture= cvCaptureFromCAM(0);
    IplImage *imgVideoCap;
    cvNamedWindow("video", CV_WINDOW_AUTOSIZE);

    if(!cvQueryFrame(cpCapture)){ cout << "Video capture failed, please check the camera." << endl;}
    else{cout << "Video camera capture status: OK" << endl;};

    while(1){

        imgVideoCap = cvQueryFrame(cpCapture);

        if(!imgVideoCap) break;

        cvShowImage("video", imgVideoCap);

        char c = cvWaitKey(33);

        if(c == 27) break;

    }

    cvReleaseCapture(&cpCapture);
    cvDestroyWindow("video");

    return 0;

}   // end of LaunchUsbCam()

int CaptureCam()
{
  int iFrame = 0;
  string stPre = "./";
  string stSuf = ".xml";
  string stSum;

  const time_t t = time(NULL);

  VideoCapture vcTest(0);

  if(!vcTest.isOpened()){

    return -1;
  }

  Mat matFrame;

  bool stop = false;

  while(!stop){
      cout << "current time is" << t << endl;

      vcTest>>matFrame;

      imshow("CamTest", matFrame);

      stSum = stPre + InttoString(iFrame) + stSuf;

      cout << stSum << endl;

      FileStorage fs(stSum, FileStorage::WRITE);
//      fs << InttoString(iFrame) << matFrame;
      iFrame++;

      if(waitKey(30) >= 0){
          stop = true;
          fs.release();

        }
  }

  FileStorage fs("./frame.xml", FileStorage::READ);
  Mat matFrameOut;
  fs["frame"] >> matFrameOut;

  imshow("outPut", matFrameOut);

  return 0;

}   // end of CaptureCam()

string InttoString(int iInput)
{
  stringstream ss;
  ss << iInput;
  string stOutput = ss.str();

  return stOutput;

}
