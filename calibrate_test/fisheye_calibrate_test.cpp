#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
//#include "opencv2/ccalib/omnidir.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void undistortFisheye(){
	std::vector <cv::Mat> inputImages;
    	std::vector<std::vector<cv::Point3f> > objectPoints(1);
    	std::vector<std::vector<cv::Point2f> > image_points;
	stringstream ss;
	string tmp;

	//Load images
	for (int i = 0; i < 14; i++)
	{
    		ss << (i+1);
		ss >> tmp;
		std::cout << "Loading: " << "/home/tomchang/opencv_test/20170926/chess" << tmp << ".jpg" << std::endl;
                inputImages.push_back(cv::imread("/home/tomchang/opencv_test/20170926/chess" + tmp + ".jpg"));
		//std::cout << "Loading: " << "/home/tomchang/opencv_test/calib_image/chessboard" << std::to_string(i + 1) << ".jpg" << std::endl;
    		//inputImages.push_back(cv::imread("/home/tomchang/opencv_test/calib_image/chessboard" + std::to_string(i + 1) + ".jpg"));
		ss.str("");
		ss.clear();
	}

	int chessBoardFlags = cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE;

	for (int i = 0; i < inputImages.size(); i++)
	{
    		std::vector<cv::Point2f> pointBuf;
    		cv::Mat view;

    		std::cout << i << std::endl;
    		bool found = cv::findChessboardCorners(inputImages[i], cv::Size(9, 6), pointBuf, chessBoardFlags);

    		if (found) // If done with success,
    		{
        		std::cout << "Corners found!" << std::endl;

        		// improve the found corners' coordinate accuracy for chessboard
        		cv::Mat viewGray;
        		cvtColor(inputImages[i], viewGray, cv::COLOR_BGR2GRAY);
        		cornerSubPix(viewGray, pointBuf, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));

        		image_points.push_back(pointBuf);

        		// Draw the corners.
    			//inputImages[i].copyTo(view);
        		//cv::drawChessboardCorners(view, cv::Size(6, 4), cv::Mat(pointBuf), found);
        		//cv::imshow("Window", view);
        		//cv::waitKey(0);
    		}   
	}
	/*	
	float squareSize = 15.0f;
	calcBoardCornerPositions(cv::Size(6, 4), squareSize, objectPoints[0]);
	objectPoints.resize(image_points.size(), objectPoints[0]);

	cv::Matx33f K;
	cv::Vec4f D;

	std::vector<cv::Vec3f> rvec;
	std::vector<cv::Vec3f> tvec;

	//int flag = cv::fisheye::CALIB_CHECK_COND | cv::fisheye::CALIB_FIX_SKEW; 
	int flag = cv::fisheye::CALIB_FIX_SKEW | cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
	//| cv::fisheye::CALIB_FIX_K1 | cv::fisheye::CALIB_FIX_K2 | cv::fisheye::CALIB_FIX_K3;// | cv::fisheye::CALIB_FIX_K4;// | cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;// | cv::fisheye::CALIB_FIX_K1;// | cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;

	cv::fisheye::calibrate(objectPoints, image_points, cv::Size(1920, 1080), K, D, rvec, tvec, flag, cv::TermCriteria(3, 20, 1e-6));

	std::cout << "Points detected" << std::endl;
	//double rms = calibrateCamera(objectPoints, image_points, cv::Size(1920, 1080), K, D, rvec, tvec, flag, cv::TermCriteria(3, 20, 1e-6));
	std::cout << "Calibrated." << std::endl;

	std::cout << K << std::endl;
	std::cout << D << std::endl;*/
	/*
	for (int i = 0; i < inputImages.size(); i++)
	{
    		cv::Mat src = cv::imread("C:/Data/CheckerboardCalib/" + std::to_string(i + 1) + ".png");
    		cv::Mat temp;

    		cv::fisheye::undistortImage(src, temp, K, D, cv::Mat::eye(3,3, CV_64F));
    		cv::imwrite("C:/Data/CheckerboardCalib/undistorted/" + std::to_string(i+1) + ".png", temp);
	}
	std::string inputLine;
	std::cin >> inputLine;*/
}

int main(int argc, char** argv){
	undistortFisheye();
	waitKey();
        return 0;
}
