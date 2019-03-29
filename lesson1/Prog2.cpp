#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

// для компиляции g++ Prog2.cpp -o Prog2 `pkg-config --cflags --libs opencv`

int main(int argc, char **argv)
{
		//переменная для хранения изображения
    Mat frame;
		//переменная для хранения потока видиозахвата
    VideoCapture cap;
		//открытие потока(-1 -- любая доступная камера)
 		cap.open(-1);
    //точка в которой будет выводится текст
    Point pt (200,400);
		// до тех пор пока поток видеозахвата открыт и можно считать изображение выводи его
    while(cap.isOpened() && cap.read(frame))
    {
			  //рисуем окружность вокруг точки нанализа
        circle (frame, Point(320,240),30,CV_RGB(255,0,0),1);
        //анализ изображения
        if (frame.at<Vec3b>(320,240)[0] - frame.at<Vec3b>(320,240)[1]> 50 &&
            frame.at<Vec3b>(320,240)[0] - frame.at<Vec3b>(320,240)[2] > 50)
              putText(frame, "Blue apple", pt, 0,2, CV_RGB(255,255,255),2);
        else  if(frame.at<Vec3b>(320,240)[1] - frame.at<Vec3b>(320,240)[0]> 40 &&
                frame.at<Vec3b>(320,240)[1] - frame.at<Vec3b>(320,240)[2] > 40)
                    putText(frame, "Green apple", pt, 0,2, CV_RGB(255,255,255),2);
        else if(frame.at<Vec3b>(320,240)[2] - frame.at<Vec3b>(320,240)[0]> 50 &&
                frame.at<Vec3b>(320,240)[2] - frame.at<Vec3b>(320,240)[1] > 50)
                    putText(frame, "Red apple", pt, 0,2, CV_RGB(255,255,255),2);
        else putText(frame, "Nothing", pt, 0,2, CV_RGB(255,255,255),2);

        imshow("image",frame);

        //вывод всех составляющих на экран
        cout << int(frame.at<Vec3b>(320,240)[0])<< " " <<int(frame.at<Vec3b>(320,240)[1])<< " " <<int(frame.at<Vec3b>(320,240)[2]) << endl;

				//если нажата клавиша EST то выходим из программы
        if (waitKey(10)==27) break;
    }
    //освобождение ресурсов
    cap.release();
    frame.release();
}
