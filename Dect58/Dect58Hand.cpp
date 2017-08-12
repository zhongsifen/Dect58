//
//  Dect58Hand.cpp
//  Dect58
//
//  Created by SIFEN ZHONG on 9/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Dect58Hand.hpp"

bool Dect58Hand::detect(cv::Mat& g, cv::Rect& face) {
	bool ret = _detect->detect(g, face);	if (!ret) return false;
	
	return true;
}

bool Dect58Hand::detect(cv::Mat& g, cv::Rect& face, int& level, double& certain) {
	bool ret = _detect->detect(g, face, level, certain);	if (!ret) return false;
	
	return true;
}
