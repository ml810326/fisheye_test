#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/ccalib/omnidir.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	
	//get image and resize
	Mat img_0 = imread("chessboard01.jpg", 0);
	int imghigh = img_0.rows;
	int imgwid = img_0.cols;
	Size dsize = Size(round(1*imgwid), round(1*imghigh));
	resize(img_0, img_0, dsize, 0, 0, INTER_AREA);
	Mat img_1 = imread("chessboard02.jpg", 0);
	resize(img_1, img_1, dsize, 0, 0, INTER_AREA);
	Mat img_2 = imread("chessboard03.jpg", 0);
	resize(img_2, img_2, dsize, 0, 0, INTER_AREA);

	Size boardSize; //chessboard
       	boardSize.width = 6;
       	boardSize.height = 4;
	
	int remaining_frames = 3; //test image
	Matx33d K;
       	Vec4d D;
       	Mat identity = Mat::eye(3, 3, CV_64F);
	
	vector<vector<Point2d> > img_points;
      	vector<vector<Point3d> > obj_points;
       	vector<Point3d> obj_temp;

	int width = 6;
       	int height = 4;
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

	cout << "Computing distortion" << endl;

	int flags = 0;// | omnidir::CALIB_FIX_SKEW | omnidir::CALIB_FIX_K1 | omnidir::CALIB_FIX_K2;
     	flags |= cv::fisheye::CALIB_FIX_SKEW;
	flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
    	flags |= cv::fisheye::CALIB_CHECK_COND;

	//Mat xi, idx, K, D;
	//TermCriteria critia(3, 200, 1e-8);
	//vector<Mat> rvecs, tvecs;
	double rms = fisheye::calibrate(obj_points, img_points, Size(320, 240), K, D, noArray(), noArray(), flags, TermCriteria(3, 20, 1e-6));
	//double rms = omnidir::calibrate(obj_points, img_points, Size(480, 270), K, xi, D, rvecs, tvecs, flags, critia, idx);
	//double _xi = xi.at<double>(0);
	cout << "Finished computing distortion" << endl;

	cout << K << endl;
      	cout << D << endl;
	cout << "rms:" << rms << endl;
	
	Mat test_result = imread("chessboard01.jpg", 0);
        resize(test_result, test_result, dsize, 0, 0, INTER_AREA);
	Mat output;
        Mat newK;
        Mat view, map1, map2;

        Size newSize(320, 240);
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
