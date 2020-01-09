#include <string>

#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.cpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    VideoCapture camera;
    camera.open(0);
    if (!camera.isOpened()) {
        cout << "Failed to open camera." << std::endl;
        return -1;
    }

    double fWidth = camera.get(CAP_PROP_FRAME_WIDTH);
    double fHeight = camera.get(CAP_PROP_FRAME_HEIGHT);
    cout << fWidth << std::endl;
    cout << fHeight << std::endl;

    /*
    640 320
    480 240
    */

    const char* window_name = "output";
    namedWindow(window_name, WINDOW_NORMAL);

    Mat frame;
    Size boardSize;
    boardSize.width = 9;
    boardSize.height = 6;

    int remaining_frames = 30;

    Mat K;//  = Mat(3, 3, CV_64F, vK);
    Mat D;
    Mat identity = Mat::eye(3, 3, CV_64F);

    vector<vector<Point2f> > img_points;
    vector<vector<Point3f> > obj_points(1);

    int sq_sz = 25;

    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            obj_points[0].push_back(Point3f(float(j * sq_sz), float(i * sq_sz), 0));
        }
    }

    obj_points.resize(remaining_frames, obj_points[0]);

    bool found = false;

    clock_t prevTimestamp = 0;
    int delay = 500;

    while (1) {

        frame = nextFrame(camera);

        bool blinkOutput = false;

        if (remaining_frames > 0) {
            vector<Point2f> corners;
            int chessBoardFlags = CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE;


            found = findChessboardCorners(frame, boardSize, corners, chessBoardFlags);


            if (found) {
                drawChessboardCorners(frame, boardSize, corners, found);
                if (clock() - prevTimestamp > delay*1e-3*CLOCKS_PER_SEC) {

                    Mat viewGray;
                    cvtColor(frame, viewGray, COLOR_BGR2GRAY);
                    cornerSubPix(viewGray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));

                    img_points.push_back(corners);
                    remaining_frames--;
                    cout << remaining_frames << " frames to calibration." << endl;
                    blinkOutput = true;
                    prevTimestamp = clock();
                }

                if (remaining_frames == 0) {
                    cout << "Computing distortion" << endl;

                    int flags = 0;
                    flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
                    flags |= cv::fisheye::CALIB_CHECK_COND;
                    flags |= cv::fisheye::CALIB_FIX_SKEW;


                    fisheye::calibrate(obj_points, img_points, frame.size(), K, D, noArray(), noArray(), flags);
                    cout << "Finished computing distortion" << endl;
                    cout << K << endl;
                    cout << D << endl;
                }
            }

            if (blinkOutput) { bitwise_not(frame, frame); }
            cv::imshow(window_name, frame);
            if (waitKey(50) == 27) {
                break;
            }
        }
        else {
            Mat output;
	    Mat newK;
	    Mat view, map1, map2;
            
	    Size newSize(1200, 1200);
	    Mat rview(newSize, frame.type());
	    
	    fisheye::estimateNewCameraMatrixForUndistortRectify(K, D, frame.size(), Matx33d::eye(), newK, 1);

	    fisheye::initUndistortRectifyMap(K, D, Matx33d::eye(), newK, frame.size(), CV_16SC2, map1, map2);

	    //fisheye::undistortImage(frame, output, K, D, identity);

	    remap(frame, rview, map1, map2, INTER_LINEAR);

            //imshow(window_name, output);
            imshow("Image View", rview);
	    imshow(window_name, frame);

	    if (waitKey(50) == 27) {
                break;
            }
        }


    }

    return 0;
}

/*
Mat output;
Mat newK;
Mat view, map1, map2;

Size newSize(1200, 1200);
Mat rview(newSize, frame.type());
//resize(rview, rview, newSize);

fisheye::estimateNewCameraMatrixForUndistortRectify(K, D, frame.size(), Matx33d::eye(), newK, 1);

fisheye::initUndistortRectifyMap(K, D, Matx33d::eye(), newK, frame.size(), CV_16SC2, map1, map2);

//fisheye::undistortImage(frame, output, K, D, identity);

remap(frame, rview, map1, map2, INTER_LINEAR);

imshow("Image View", rview);
imshow(window_name, frame);

if (waitKey(50) == 27) {
	break;
}
*/
