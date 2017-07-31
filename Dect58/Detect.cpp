// Detect.cpp

#include "Detect.hpp"
using namespace cv;

Detect::Detect(std::string filename)
{
	this->status = 0;

	bool ret = false;
	
	ret = this->cascade.load(filename);		if (!ret) return;

	this->status = 1;
}

bool
Detect::detect(cv::Mat& g, cv::Rect& face)
{
	if (this->status < 1) return false;

	std::vector<Rect> list;
	this->cascade.detectMultiScale(g, list);
	int n = (int)list.size();		if (n < 1) return false;
	face = list[0];
	for (int i=1; i<n; i++) {
		if (list[i].area() > face.area()) {
			face = list[i];
		}
	}
	
	this->status = 2;

	return true;
}

bool
Detect::detect_list(cv::Mat& g, std::vector<cv::Rect>& list)
{
	if (this->status < 1) return false;
	
	this->cascade.detectMultiScale(g, list);
	int n = (int)list.size();		if (n < 1) return false;
	
	this->status = 2;
	
	return true;
}

bool
Detect::detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& face)
{
	if (this->status < 1) return false;

	cv::Mat h = g(roi);
	
	std::vector<Rect> list;
	this->cascade.detectMultiScale(h, list);
	int n = (int)list.size();		if (n < 1) return false;
	face = list[0];
	for (int i=1; i<n; i++) {
		if (list[i].area() > face.area()) {
			face = list[i];
		}
	}

	face.x += roi.x;
	face.y += roi.y;
	
	this->status = 2;
	
	return true;
}
