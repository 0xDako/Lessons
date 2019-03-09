#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
//g++ 1.cpp -o main `pkg-config --cflags --libs opencv`

int main(int argc, char* argv[])
{
	// получаем любую подключённую камеру
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
	assert( capture );

	IplImage* frame=0;

	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter=0;
	char filename[512];

	while(true){
		// получаем кадр
		frame = cvQueryFrame( capture );

		// показываем
		cvShowImage("capture", frame);

		char c = cvWaitKey(33);
		if (c == 27) { // нажата ESC
			break;
		}
		else if(c == 13) { // Enter
			// сохраняем кадр в файл
			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;
		}
	}
	// освобождаем ресурсы
	cvReleaseCapture( &capture );
	cvDestroyWindow("capture");
	return 0;
}
