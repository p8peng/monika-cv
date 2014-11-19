#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

string         MatOutTest(unsigned long ulTime);
unsigned long searchApproximateFrame(unsigned long input, vector <unsigned long> &arr, int n);

string         InttoString(int iInput);
string         UlongtoString(unsigned long ulInput);
void           FiletoVector();

vector<unsigned long>  vecTime;

int main(int argc, const char * argv[]) {
    // insert code here...

//    unsigned long ulTest = 1416331626929;
    argv[0] = ulTimestamp;
    cout << MatOutTest(argv[0]) << endl;

    return 0;
}

string MatOutTest(unsigned long ulTime)
{
    Mat matImageOut;
    string strFile, strImage;
    unsigned long ulExactTime;

    FiletoVector();
    ulExactTime = searchApproximateFrame(ulTime, vecTime, vecTime.size());

    cout << ulExactTime << endl;

    FileStorage fs("/u5/j49zheng/Work/monika-cv/Framee.xml", FileStorage::READ);

    strFile = "Frame" + UlongtoString(ulExactTime);

    cout << strFile << endl;

    fs[strFile] >> matImageOut;
    strImage = strFile + ".jpg";
    imwrite(strImage, matImageOut);

    fs.release();
    vecTime.clear();

    return strImage;

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

void FiletoVector()
{
  unsigned long ulTemp;
  string strSum, strTimeStamp;

  FileStorage fsTime("/u5/j49zheng/Work/monika-cv/TimeStamp.xml", FileStorage::READ);

  fsTime["Sum"] >> strSum;

  int iSum = atoi(strSum.c_str());

  for(int i = 1; i <= iSum; i++){
    fsTime["Time" + InttoString(i)] >> strTimeStamp;
    ulTemp = atoll(strTimeStamp.c_str());

    vecTime.push_back(ulTemp);

  }

}
