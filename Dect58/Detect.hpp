// Detect.hpp

#ifndef _Detect_
#define _Detect_

#include "Dect58.hpp"

class Detect {
protected:
	int status;
	cv::CascadeClassifier cascade;
public:
	Detect();
	Detect(std::string filename);
	bool detect(cv::Mat& g, cv::Rect& face);
	bool detect_list(cv::Mat& g, std::vector<cv::Rect>& list);
	bool detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& face);
};

#endif
