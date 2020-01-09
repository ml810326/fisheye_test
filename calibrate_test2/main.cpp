#include "calibration.h"

int main(){ 
    CameraCalibrator myCameraCalibrator; 
    myCameraCalibrator.setFilename(); 
    myCameraCalibrator.setBorderSize(Size(6,4)); 
    myCameraCalibrator.addChessboardPoints();

    Mat src = imread("chessboard9.jpg",0);
    Size newSize(1280, 720);
    Mat dst(newSize, src.type());
    myCameraCalibrator.calibrate(src, dst);

    imshow("Original Image", src);
    imshow("Undistorted Image", dst);
    waitKey();
    return 0;
}
