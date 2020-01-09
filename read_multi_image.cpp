#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	
	//get image and resize
	Mat img_0 = imread("sta_test_6.jpg", 0);
	int imghigh = img_0.rows;
	int imgwid = img_0.cols;
	//cout << "imghigh" << imghigh << endl;
	//cout << "imgwid" << imgwid << endl;
	Size dsize = Size(round(2*imgwid/3), round(2*imghigh/3));
	resize(img_0, img_0, dsize, 0, 0, INTER_AREA);
	Mat img_1 = imread("sta_test_7.jpg", 0);
	resize(img_1, img_1, dsize, 0, 0, INTER_AREA);
	Mat img_2 = imread("sta_test_8.jpg", 0);
	resize(img_2, img_2, dsize, 0, 0, INTER_AREA);
	Mat img_3 = imread("sta_test_9.jpg", 0);
	resize(img_3, img_3, dsize, 0, 0, INTER_AREA);
	Mat img_4 = imread("sta_test_10.jpg", 0);
	resize(img_4, img_4, dsize, 0, 0, INTER_AREA);
	Mat img_5 = imread("sta_test_17.jpg", 0);
        resize(img_5, img_5, dsize, 0, 0, INTER_AREA);
	Mat img_6 = imread("sta_test_12.jpg", 0);
        resize(img_6, img_6, dsize, 0, 0, INTER_AREA);
	Mat img_7 = imread("sta_test_13.jpg", 0);
        resize(img_7, img_7, dsize, 0, 0, INTER_AREA);
	Mat img_8 = imread("sta_test_14.jpg", 0);
        resize(img_8, img_8, dsize, 0, 0, INTER_AREA);
	Mat img_9 = imread("sta_test_15.jpg", 0);
        resize(img_9, img_9, dsize, 0, 0, INTER_AREA);
	Mat img_10 = imread("sta_test_16.jpg", 0);
        resize(img_10, img_10, dsize, 0, 0, INTER_AREA);

	Size boardSize; //chessboard
       	boardSize.width = 9;
       	boardSize.height = 6;
	
	int remaining_frames = 9; //test image
	Matx33d K;
       	Vec4d D;
       	Mat identity = Mat::eye(3, 3, CV_64F);
	
	vector<vector<Point2d> > img_points;
      	vector<vector<Point3d> > obj_points;
       	vector<Point3d> obj_temp;

	int width = 9;
       	int height = 6;
      	int sq_sz = 27;

	for (int i = 0; i < width; i++) {
            	for (int j = 0; j < height; j++) {
                  	obj_temp.push_back(Point3d(double(j * sq_sz), double(i * sq_sz), 0));
             	}
    	}
  	for (int i = 0; i < remaining_frames; i++)
           	obj_points.push_back(obj_temp);
	//get feature point
	vector<Point2f> corners;
	bool found = findChessboardCorners(img_0, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
	drawChessboardCorners(img_0, boardSize, corners, found);
	namedWindow("chess1");
	imshow("chess1", img_0);
	vector<Point2d> img_temp1;
	for (int i = 0; i < width*height; i++){
        	Point2d temp1 = corners[i];
              	img_temp1.push_back(temp1);
    	}
   	img_points.push_back(img_temp1);

        found = findChessboardCorners(img_1, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_1, boardSize, corners, found);
        namedWindow("chess2");
        imshow("chess2", img_1);
	vector<Point2d> img_temp2;
        for (int i = 0; i < width*height; i++){
                Point2d temp2 = corners[i];
                img_temp2.push_back(temp2);
        }
        img_points.push_back(img_temp2);

        found = findChessboardCorners(img_2, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_2, boardSize, corners, found);
        namedWindow("chess3");
        imshow("chess3", img_2);
	vector<Point2d> img_temp3;
        for (int i = 0; i < width*height; i++){
                Point2d temp3 = corners[i];
                img_temp3.push_back(temp3);
        }
        img_points.push_back(img_temp3);

        found = findChessboardCorners(img_3, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_3, boardSize, corners, found);
        namedWindow("chess4");
        imshow("chess4", img_3);
	vector<Point2d> img_temp4;
        for (int i = 0; i < width*height; i++){
                Point2d temp4 = corners[i];
                img_temp4.push_back(temp4);
        }
        img_points.push_back(img_temp4);

	found = findChessboardCorners(img_4, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_4, boardSize, corners, found);
        namedWindow("chess5");
        imshow("chess5", img_4);
	vector<Point2d> img_temp5;
        for (int i = 0; i < width*height; i++){
                Point2d temp5 = corners[i];
                img_temp5.push_back(temp5);
        }
        img_points.push_back(img_temp5);
	
	found = findChessboardCorners(img_5, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_5, boardSize, corners, found);
        namedWindow("chess6");
        imshow("chess6", img_5);
        vector<Point2d> img_temp6;
        for (int i = 0; i < width*height; i++){
                Point2d temp6 = corners[i];
                img_temp6.push_back(temp6);
        }
        img_points.push_back(img_temp6);

	found = findChessboardCorners(img_6, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_6, boardSize, corners, found);
        namedWindow("chess7");
        imshow("chess7", img_6);
        vector<Point2d> img_temp7;
        for (int i = 0; i < width*height; i++){
                Point2d temp7 = corners[i];
                img_temp7.push_back(temp7);
        }
        img_points.push_back(img_temp7);

	found = findChessboardCorners(img_7, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_7, boardSize, corners, found);
        namedWindow("chess8");
        imshow("chess8", img_7);
        vector<Point2d> img_temp8;
        for (int i = 0; i < width*height; i++){
                Point2d temp8 = corners[i];
                img_temp8.push_back(temp8);
        }
        img_points.push_back(img_temp8);

	found = findChessboardCorners(img_8, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_8, boardSize, corners, found);
        namedWindow("chess9");
        imshow("chess9", img_8);
        vector<Point2d> img_temp9;
        for (int i = 0; i < width*height; i++){
                Point2d temp9 = corners[i];
                img_temp9.push_back(temp9);
        }
        img_points.push_back(img_temp9);
	/*
	found = findChessboardCorners(img_9, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_9, boardSize, corners, found);
        namedWindow("chess10");
        imshow("chess10", img_9);
        vector<Point2d> img_temp10;
        for (int i = 0; i < width*height; i++){
                Point2d temp10 = corners[i];
                img_temp10.push_back(temp10);
        }
        img_points.push_back(img_temp10);
	
	found = findChessboardCorners(img_10, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
        drawChessboardCorners(img_10, boardSize, corners, found);
        namedWindow("chess11");
        imshow("chess11", img_10);
        vector<Point2d> img_temp11;
        for (int i = 0; i < width*height; i++){
                Point2d temp11 = corners[i];
                img_temp11.push_back(temp11);
        }
        img_points.push_back(img_temp11);
	*/
	cout << "Computing distortion" << endl;

	int flags = 0;
     	flags |= cv::fisheye::CALIB_FIX_SKEW;
	flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
    	//flags |= cv::fisheye::CALIB_CHECK_COND;
	//flags |= cv::fisheye::CALIB_FIX_K1;
	//flags |= cv::fisheye::CALIB_FIX_K2;
	//flags |= cv::fisheye::CALIB_FIX_K3;
	//flags |= cv::fisheye::CALIB_FIX_K4;

	double rms = fisheye::calibrate(obj_points, img_points, Size(1280, 720), K, D, noArray(), noArray(), flags, TermCriteria(3, 20, 1e-6));
	
	cout << "Finished computing distortion" << endl;

	cout << K << endl;
      	cout << D << endl;
	cout << "rms:" << rms << endl;

	Mat test_result = imread("sta_test_6.jpg", 0);
        resize(test_result, test_result, dsize, 0, 0, INTER_AREA);
	Mat output;
        Mat newK;
        Mat view, map1, map2;

        Size newSize(1280, 720);
        Mat rview(newSize, test_result.type());
        //resize(rview, rview, newSize);

        fisheye::estimateNewCameraMatrixForUndistortRectify(K, D, test_result.size(), Matx33d::eye(), newK, 1);

        fisheye::initUndistortRectifyMap(K, D, Matx33d::eye(), newK, test_result.size(), CV_16SC2, map1, map2);

        //fisheye::undistortImage(frame, output, K, D, identity);

        remap(test_result, rview, map1, map2, INTER_LINEAR);

	//Mat output;
       	fisheye::undistortImage(test_result, output, K, D, identity);
      	namedWindow("Origin");
        imshow("Origin", test_result);
	namedWindow("Display");
	imshow("Display", output);
	namedWindow("Test");
	imshow("Test", rview);
       	waitKey();


	return 0;
}
