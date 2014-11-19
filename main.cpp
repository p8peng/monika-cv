//
//  main.cpp
//  Keyboarding Monitoring
//
//  Created by Peng Peng on 2014-11-01.
//  Copyright (c) 2014 彭 彭. All rights reserved.
//

#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

void           HandDetection();
int            LaunchDefCam();
int            LaunchUsbCam();
int            CaptureCam();
void           MatOutTest(unsigned long iTime);
unsigned long  searchApproximateFrame(unsigned long input, vector <unsigned long> &arr, int n);


string  InttoString(int iInput);
string  UlongtoString(unsigned long ulInput);

vector<unsigned long>  vecTime;

int main(int argc, const char * argv[]) {
    // insert code here...

//    LaunchDefCam();
//    LaunchUsbCam();

//    HandDetection();
    unsigned long ulTest = 1416331626929;
    CaptureCam();
    MatOutTest(ulTest);

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
  string stPre = "Frame";
  string stSum, stTime;

  struct timeval  tm;
  unsigned long   ms;

  VideoCapture vcTest(1);

  if(!vcTest.isOpened()){

    return -1;
  }

  Mat matFrame;

  bool stop = false;

  FileStorage fs("/u5/j49zheng/Work/monika-cv/Framee.xml", FileStorage::WRITE);
  while(!stop){

      gettimeofday(&tm, NULL);
      ms = tm.tv_sec * 1000 + tm.tv_usec / 1000;
      stTime = UlongtoString(ms);
      vecTime.push_back(ms);

      vcTest>>matFrame;

      imshow("CamTest", matFrame);

      stSum = stPre + stTime;

//      FileStorage fs("/u5/j49zheng/Work/monika-cv/Framee.xml", FileStorage::WRITE);
      fs << stSum << matFrame;

      cout << matFrame.cols << endl;

      if(waitKey(30) >= 0){
          stop = true;
          fs.release();

        }
  }

  return 0;

}   // end of CaptureCam()

void MatOutTest(unsigned long ulTime)
{
    Mat matImageOut;
    string strFile, strImage;
    unsigned long ulExactTime;

    ulExactTime = searchApproximateFrame(ulTime, vecTime, vecTime.size());

    cout << ulExactTime << endl;

    FileStorage fs("/u5/j49zheng/Work/monika-cv/Framee.xml", FileStorage::READ);

    strFile = "Frame" + UlongtoString(ulExactTime);

    cout << strFile << endl;

    fs[strFile] >> matImageOut;
    strImage = strFile + ".jpg";
    imwrite(strImage, matImageOut);

    cout << matImageOut.cols << endl;

    fs.release();
    vecTime.clear();

}   // end of MatOutTest()

string InttoString(int iInput)
{
  stringstream ss;
  ss << iInput;
  string stOutput = ss.str();

  return stOutput;

}

string UlongtoString(unsigned long ulInput)
{
  stringstream ss;
  ss << ulInput;
  string stOutput = ss.str();

  return stOutput;

}

unsigned long searchApproximateFrame(unsigned long input, vector <unsigned long> &arr, int n)
{
  int l, r, m;
  l = 0;
  r = n - 1;
  while(l <= r) {
    m = (l + r) >> 1;
    if (arr[m] > input) {
      r = m - 1;
    } else if (arr[m] < input) {
      l = m + 1;
    } else {
      break;
    }
  }
  return arr[m];
}
