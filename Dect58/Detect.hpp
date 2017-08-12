// Detect.hpp

#ifndef _Detect_
#define _Detect_

#include "Dect58.hpp"

class Detect {
protected:
	int status;
	cv::CascadeClassifier cascade;
public:
	Detect(std::string filename=Dect58::RES + "haarcascades/haarcascade_frontalface_alt2.xml");
	bool detect(cv::Mat& g, cv::Rect& face);
	bool detect_list(cv::Mat& g, std::vector<cv::Rect>& list);
	bool detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& face);
	
	bool detect(cv::Mat& g, cv::Rect& face, int& level, double& certain);
};

#endif

#if 0
Mat img;
vector<double> weights;
vector<int> levels;
vector<Rect> detections;
CascadeClassifier model("/path/to/your/model.xml");
model.detectMultiScale(img, detections, levels, weights, 1.1, 3, 0, Size(), Size(), true);
cerr << "Detection " << detections[0] << " with weight " << weights[0] << endl;

#endif
