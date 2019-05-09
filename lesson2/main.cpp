#include "opencv2/opencv.hpp"
#include <iostream>
#include "colors.h"

using namespace cv;
using namespace std;

// для компиляции g++ main.cpp -o main `pkg-config --cflags --libs opencv`

int main(int argc, char **argv)
{
		//переменная для хранения изображения
    Mat frame;
		//переменная для хранения потока видиозахвата
    VideoCapture cap;
		//открытие потока(-1 -- любая доступная камера)
 		cap.open(-1);
    while(cap.isOpened() && cap.read(frame))
    {
      
    }
    //освобождение ресурсов
    cap.release();
    frame.release();

  }
