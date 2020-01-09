#include <string>                                                                                   
#include <opencv2/opencv.hpp>                                                                       
//#include <opencv2/core/core.cpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

    using namespace cv;
    using namespace std;

    int main(int argc, char** argv) {

	    String imageName("fisheye_test9.jpg"); //read image
	    VideoCapture cap("fisheye_test%d.jpg");
            if (!cap.isOpened()) {
                    cout << "Failed to open picture" << std::endl;
                    return -1;
            }

            const char* window_name = "output"; //output window
            namedWindow(window_name);

            Mat frame;
	    frame = imread(imageName, IMREAD_COLOR);

            Size boardSize; //chessboard
            boardSize.width = 9;
            boardSize.height = 6;

            int remaining_frames = 5; //read 5 images
            Matx33d K;
            Vec4d D;
            Mat identity = Mat::eye(3, 3, CV_64F);

            vector<vector<Point2d> > img_points;
            vector<vector<Point3d> > obj_points;
            vector<Point3d> obj_temp;

            int width = 9;
            int height = 6;
            int sq_sz = 30;

            for (int i = 0; i < width; i++) {
                    for (int j = 0; j < height; j++) {
                            obj_temp.push_back(Point3d(double(j * sq_sz), double(i * sq_sz), 0));
                    }
            }
            for (int i = 0; i < remaining_frames; i++)
                    obj_points.push_back(obj_temp);
           

            while (cap.isOpened()) {
                    //if (!camera.read(frame)) {  //camera image read
                      //      cout << "Failed to read frame" << std::endl;
                        //    break;
                    //}
		    Mat img;
		    cap.read(img);
                    //if (remaining_frames > 0) { //get test image
                            vector<Point2f> corners;
                            bool found = findChessboardCorners(frame, boardSize, corners,
                                    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);
                            drawChessboardCorners(frame, boardSize, corners, found);
                            imshow(window_name, frame);
			    //if (found && waitKey(30)==32)  {
                                    vector<Point2d> img_temp;
                                    for (int i = 0; i < width*height; i++)
                                    {
                                            Point2d temp = corners[i];
                                            img_temp.push_back(temp);
                                    }
                                    img_points.push_back(img_temp);
                                    //remaining_frames--;
				    
                                    //cout << remaining_frames << " frames to calibration." << endl;
	    }
                                    //if (remaining_frames == 0) {
                                            cout << "Computing distortion" << endl;

                                            int flags = 0;
                                            flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
                                            flags |= cv::fisheye::CALIB_CHECK_COND;
                                            flags |= cv::fisheye::CALIB_FIX_SKEW;

                                            fisheye::calibrate(obj_points, img_points, Size(640, 480), K, D,
                                                    noArray(), noArray(), flags, TermCriteria(3, 20, 1e-6));
                                            cout << "Finished computing distortion" << endl;
                                    //}
                            //}

                            //imshow(window_name, frame);
                            //waitKey(1);
                    //}
                    //else {
                            Mat output;
                            fisheye::undistortImage(frame, output, K, D, identity);
                            imshow(window_name, output);
                            waitKey(1);
                    //}

                    //if (waitKey(30) > 0) {
                    //        break;
                    //}
            //}

            return 0;
    }
