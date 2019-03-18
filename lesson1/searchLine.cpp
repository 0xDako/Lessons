#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

// для компиляции g++ searchLine.cpp -o searchLine `pkg-config --cflags --libs opencv`

int main(int argc, char **argv)
{
		//переменная для хранения изображения
    Mat frame;
		//переменная для хранения потока видиозахвата
    VideoCapture cap;
		//открытие потока(-1 -- любая доступная камера)
 		cap.open(-1);
    //переменная для хранения координаты линии
    int line = 320;
		// до тех пор пока поток видеозахвата открыт и можно считать изображение выводи его
    while(cap.isOpened() && cap.read(frame))
    {
        //номер анализируемой строки
        int N = 470;
        //массив для хранения найденных линий
        int mas[640];
        //счетчик массива
        int r = 0;
        //начало конец и длина линии линии
        int start = 0, finish = 0, lenline = 0;
        //
        for (int i = 0; i < frame.cols; i++){
          //считаем что это начало линии
          start = i;
          while ((i < frame.cols) && ((frame.at<Vec3b>(N, i)[2]) < 70) && ((frame.at<Vec3b>(N, i)[1]) < 70) && ((frame.at<Vec3b>(N, i)[0]) < 70)) // если черный или темный
          {
    			     i++; // перебираем линию
          }
          //после перебора конец линии
          finish = i;
          //находим длину линии
          lenline = finish - start;
          //если длина линии слишком маленькая пропускаем ее
          if (lenline < 50)  continue;
          //если линиия подходящего размера добавляем ее в массив
          mas[r] = (finish + start)/2;
          r++;
         }
        //Находим блтжащюю линию к линии на предыдущем кадре
        int min = mas[0];

    		for (int i = 0; i < r; i++)
    		{
          if (abs(mas[i] - line) < min) min = mas[i];
        }
        //линия имеющая минимально отклонение и есть новая линия
        line = min;
        //отображаем в консоль полученную линию
        cout<<line<<endl;
        //для наглядности рисуем круг на месте линии
        circle (frame, Point(min,N),10,CV_RGB(255,0,0),1,1);
        //выводим изображение в окно с именем "image"
        imshow("image",frame);
				//если нажата клавиша EST то выходим из программы
        if (waitKey(10)==27) break;
    }
    //освобождение ресурсов
    cap.release();
    frame.release();

}
