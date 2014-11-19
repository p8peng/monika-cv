#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

int     CaptureCam();

string  InttoString(int iInput);
string  UlongtoString(unsigned long ulInput);

int main(int argc, const char * argv[]) {
    // insert code here...

    unsigned long ulTest = 1416331626929;
    CaptureCam();

    return 0;
}

int CaptureCam()
{
  string stPre = "Frame";
  string stSum, stTime;

  struct timeval  tm;
  unsigned long   ms;

  int iTimeIndex = 1;

  VideoCapture vcTest(1);

  if(!vcTest.isOpened()){

    return -1;
  }

  Mat matFrame;

  bool stop = false;

  FileStorage fs("/u5/j49zheng/Work/monika-cv/Framee.xml", FileStorage::WRITE);
  FileStorage fsTime("/u5/j49zheng/Work/monika-cv/TimeStamp.xml", FileStorage::WRITE);

  while(!stop){

      gettimeofday(&tm, NULL);
      ms = tm.tv_sec * 1000 + tm.tv_usec / 1000;
      stTime = UlongtoString(ms);

      fsTime << "Time" + InttoString(iTimeIndex) << stTime;

      vcTest >> matFrame;

      imshow("CamTest", matFrame);

      stSum = stPre + stTime;

      fs << stSum << matFrame;

      iTimeIndex++;

      if(waitKey(30) >= 0){
          stop = true;

          fsTime << "Sum" << InttoString(iTimeIndex);
          fs.release();
          fsTime.release();

        }
  }

  return 0;

}   // end of CaptureCam()

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
