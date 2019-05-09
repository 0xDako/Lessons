#include "opencv2/opencv.hpp"
#include <iostream>
#include "colors.h"

using namespace cv;
using namespace std;


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
      //переменная для хранения ЧБ изображени
      Mat gray_img, img;
      //размытие изображения для уменьшения цветового мусора
      GaussianBlur(frame, frame, Size(3, 3), 0);
      //делаем копии изображения для дальнейшей работы
  		frame.copyTo(gray_img);
      frame.copyTo(img);
      //переводим изображение в ЧБ
  		cvtColor(gray_img, gray_img, CV_BGR2GRAY);
      //вектор для хранения контуров
  		vector<vector<Point>> contours;
      //вектор для хранения отдельного контура
      vector<Point> approx;
      //нахождение границ на изображении
      Canny(gray_img, gray_img, 10, 200, 3);
      //нахождение контуров на изображнии
      findContours(gray_img, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
      //цикл для перебора всех контуров
      for (size_t i = 0; i<contours.size(); i++){
          //апроксимируем каждый контур до простой фигуры
          approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.03, true);
          //находим площадь анализируемого контура
          double area = fabs(contourArea((Mat)contours[i]));

          //проверяем площадь полученного контура и его замкнутость
          if (area < 10000 || area > 200000 || !isContourConvex(approx)) continue;
          //если количество углов у контура равно трем обводим его
          if (approx.size() == 3 )
		        {
              //находим минимальный прямоугольни обрамляющий контур
              Rect boundingarea = boundingRect(approx);
              //рисуем его на картинке
              rectangle(img, boundingarea, Scalar(255), 5, 8, 0);
              //вывод в консоль информации распознаной фигуре
              cout << "Треугольник" <<endl;
              //вырезаем распознаную фигуру из всего изображения
              Mat roi = frame(boundingarea);
              //подсчитываем кол-во цветов на выреззаной фигуре
              imshow("ROI",roi);
              vector<int> colors = ColorAnalys(roi);
              cout <<"red:"<<colors[0]<<" green:"<<colors[1]<<" blue:"<<colors[2]<< endl;
            }
      }
    //выводим картинку с контурами
    imshow("gray",gray_img);
	  //выводим само изображение
    imshow("image",img);
		//если нажата клавиша EST то выходим из программы
    if (waitKey(5)==27) break;
    }
    //освобождение ресурсов
    cap.release();
    frame.release();

}
