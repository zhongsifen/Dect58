//
//  Dect58.hpp
//  Dect58
//
//  Created by SIFEN ZHONG on 13/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Dect58_hpp
#define Dect58_hpp

#include "Dect58UI.hpp"
#include "_opencv2.hpp"

class Dect58 {
	int status;
	cv::CascadeClassifier cascade;
public:
	Dect58() { this->status = 0; }
	Dect58(std::string filename);
	
	bool detect(cv::Mat& g, cv::Rect& box);
	bool detect_list(cv::Mat& g, std::vector<cv::Rect>& list);
	bool detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& box);
	
	bool detect(cv::Mat& g, cv::Rect& box, int& level, double& weight);	
};

#endif /* Dect58_hpp */
