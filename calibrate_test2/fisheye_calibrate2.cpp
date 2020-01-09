#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/ccalib/omnidir.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

static void calcChessboardCorners(Size boardSize, double square_width, double square_height,
    Mat& corners)
{
    // corners has type of CV_64FC3
    corners.release();
    int n = boardSize.width * boardSize.height;
    corners.create(n, 1, CV_64FC3);
    Vec3d *ptr = corners.ptr<Vec3d>();
    for (int i = 0; i < boardSize.height; ++i)
    {
        for (int j = 0; j < boardSize.width; ++j)
        {
            ptr[i*boardSize.width + j] = Vec3d(double(j * square_width), double(i * square_height), 0.0);
        }
    }
}

static bool readStringList( const string& filename, vector<string>& l )
{
    l.resize(0);
    FileStorage fs(filename, FileStorage::READ);
    if( !fs.isOpened() )
        return false;
    FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != FileNode::SEQ )
        return false;
    FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it )
        l.push_back((string)*it);
    return true;
}

int main(int argc, char** argv){
	
	//get image and resize
	Size imageSize;
	Mat img_0 = imread("chessboard1.jpg", 0);
	int imghigh = img_0.rows;
	int imgwid = img_0.cols;
	imageSize = img_0.size();
	Size dsize = Size(round(1*imgwid), round(1*imghigh));
	resize(img_0, img_0, dsize, 0, 0, INTER_AREA);
	Mat img_1 = imread("chessboard2.jpg", 0);
	resize(img_1, img_1, dsize, 0, 0, INTER_AREA);
	Mat img_2 = imread("chessboard3.jpg", 0);
	resize(img_2, img_2, dsize, 0, 0, INTER_AREA);

	Size boardSize; //chessboard
       	boardSize.width = 6;
       	boardSize.height = 4;
	
	int remaining_frames = 3; //test image
	//Matx33d K;
       	//Vec4d D;
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
	vector<Point2d> img_temp1;
	for (int i = 0; i < width*height; i++){
        	Point2d temp1 = corners[i];
              	img_temp1.push_back(temp1);
    	}
   	img_points.push_back(img_temp1);

        found = findChessboardCorners(img_1, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
	vector<Point2d> img_temp2;
        for (int i = 0; i < width*height; i++){
                Point2d temp2 = corners[i];
                img_temp2.push_back(temp2);
        }
        img_points.push_back(img_temp2);

        found = findChessboardCorners(img_2, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
	vector<Point2d> img_temp3;
        for (int i = 0; i < width*height; i++){
                Point2d temp3 = corners[i];
                img_temp3.push_back(temp3);
        }
        img_points.push_back(img_temp3);

	cout << "Computing distortion" << endl;
	
	// calculate object coordinates
    	printf("calculate object coordinates\n");
    	Mat object;
    	//calcChessboardCorners(boardSize, square_width, square_height, object);
	/*
	calcChessboardCorners(boardSize, sq_sz, sq_sz, object);
    	for(int i = 0; i < (int)detec_list.size(); ++i)
        	objectPoints.push_back(object);
	*/
    	// run calibration, some images are discarded in calibration process because they are failed
    	// in initialization. Retained image indexes are in idx variable.
    	printf("run calibration\n");
	int flags = 0 | omnidir::CALIB_FIX_SKEW | omnidir::CALIB_FIX_K1 | omnidir::CALIB_FIX_K2;
    	Mat K, D, xi, idx;
    	vector<Vec3d> rvecs, tvecs;
    	double _xi, rms;
    	TermCriteria criteria(3, 200, 1e-8);
	printf("test rms\n");
    	rms = omnidir::calibrate(obj_points, img_points, imageSize, K, xi, D, rvecs, tvecs, flags, criteria, idx);
    	//rms = omnidir::calibrate(objectPoints, imagePoints, imageSize, K, xi, D, rvecs, tvecs, flags, criteria, idx);
	_xi = xi.at<double>(0);
	printf("rms: %f\n", rms);
    	//saveCameraParams(outputFilename, flags, K, D, _xi, rvecs, tvecs, detec_list, idx, rms, imagePoints);

	return 0;
}
