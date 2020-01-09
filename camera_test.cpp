#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main()
{
	Mat image, image2;
	VideoCapture cap, cap2;
	cap.open(0);
	cap2.open(0);

	while(cap.isOpened())
	{
		cap>>image;
		imshow("Webcam live", image);
		if(waitKey(33) == 27)
			break;
	}
	
	return 0;
}
