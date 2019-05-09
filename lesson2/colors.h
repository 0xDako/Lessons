#include "opencv2/opencv.hpp"
#include "vector"

using namespace std;
using namespace cv;

vector<int> ColorAnalys(Mat frame){

  int NumR = 0,
      NumG = 0,
      NumB = 0,
      r    = 0,
      g    = 0,
      b    = 0;

  for (int j = 0;j<frame.cols;j++){
      for (int i = 0;i<frame.rows;i++){
        r = frame.at<Vec3b>(i, j)[2];
        g = frame.at<Vec3b>(i, j)[1];
        b = frame.at<Vec3b>(i, j)[0];
        if (r-g > 50 && r-b > 50) NumR++;
        if (g-r > 50 && g-b > 50) NumG++;
        if (b-g > 50 && b-r > 50) NumB++;
    }
  }

  vector<int> v;
  v.push_back(NumR);
  v.push_back(NumG);
  v.push_back(NumB);

  return v;

}
