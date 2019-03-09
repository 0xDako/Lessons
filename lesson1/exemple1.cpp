#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

// для компиляции g++ test.cpp -o test `pkg-config --cflags --libs opencv`

int main(int argc, char **argv)
{
		//переменная для хранения изображения
    Mat frame;
		//переменная для хранения потока видиозахвата
    VideoCapture cap;
		//открытие потока(-1 -- любая доступная камера)
 		cap.open(-1);
		// до тех пор пока поток видеозахвата открыт и можно считать изображение выводи его
    while(cap.isOpened() && cap.read(frame))
    {
        Point pt (100,100);
				//выводим изображение в окно с именем "image"
        if (int(frame.at<Vec3b>(240,320)[0])>150)putText(frame, "Red apple", pt, FONT_HERSHEY_SCRIPT_SIMPLEX,2, CV_RGB(100,0,200));
        else if (int(frame.at<Vec3b>(240,320)[1])>150) putText(frame, "Green apple", pt, FONT_HERSHEY_SCRIPT_SIMPLEX,2, CV_RGB(100,0,200));
        else if (int(frame.at<Vec3b>(240,320)[2])>150) putText(frame, "Blue apple", pt, FONT_HERSHEY_SCRIPT_SIMPLEX,2, CV_RGB(100,0,200));
        else putText(frame, "Nothing", pt, FONT_HERSHEY_SCRIPT_SIMPLEX,2, CV_RGB(100,0,200));
        imshow("image",frame);


				//если нажата клавиша EST то выходим из программы
        if (waitKey(10)==27) break;
    }
}
