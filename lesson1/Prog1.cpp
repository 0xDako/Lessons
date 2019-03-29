#include "opencv2/opencv.hpp"
using namespace cv;

// для компиляции g++ Prog1.cpp -o Prog1 `pkg-config --cflags --libs opencv`

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
				//выводим изображение в окно с именем "image"
        imshow("image",frame);
				//если нажата клавиша EST то выходим из программы
        if (waitKey(10)==27) break;
    }
    //освобождение ресурсов
    cap.release();
    frame.release();

}
