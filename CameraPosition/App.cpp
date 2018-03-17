#include<opencv2\opencv.hpp>
#include<opencv2\aruco.hpp>
using namespace std;
using namespace cv;
#define devView(i) imshow(#i,i)

int main()
{
	VideoCapture cam(0);
	if (!cam.isOpened()) return -1;
	Mat frame; cam >> frame;

	double camD[9] = { 5.9727068720802993e+02, 0., 3.2496668565093159e+02, 0.,
		5.9869204759667093e+02, 2.3725735917180347e+02, 0., 0., 1.};
	double distCoeffD[5] = { 7.6762365397558804e-02, -6.2901589712362121e-02,
		2.0949959381061679e-03, 1.6222783186584377e-03,
		-3.8407765897706686e-01 };

	Mat cameraMatrix = Mat(3, 3, CV_64FC1, camD);
	Mat distCoeffs = Mat(5, 1, CV_64FC1, distCoeffD);
	auto dict = aruco::getPredefinedDictionary(aruco::DICT_5X5_250);
	std::vector<int> ids;
	std::vector<std::vector<cv::Point2f>> corners;
	aruco::DetectorParameters dpara;
	dpara.cornerRefinementMethod = aruco::CORNER_REFINE_SUBPIX;
	for (Mat f2; waitKey(1) != 27; cam >> frame)
	{

		frame.copyTo(f2);
 		aruco::detectMarkers(f2, dict, corners, ids);
		if (ids.size() > 0) {
			cv::aruco::drawDetectedMarkers(f2, corners, ids);
			std::vector<cv::Vec3d> rvecs, tvecs;
			cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
			// draw axis for each marker
			for (int i = 0; i<ids.size(); i++)
			cv::aruco::drawAxis(f2, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
			
			//cv::aruco::
		}
		//devView(frame);
		flip(f2, f2, 1);
		devView(f2);
	}
}