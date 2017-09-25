//
//  Dect58Face.cpp
//  Dect58
//
//  Created by SIFEN ZHONG on 31/7/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Dect58Face.hpp"
using namespace cv;

bool
Dect58Face::detect(cv::Mat &g, cv::Rect &box) {
	bool ret = dectFace.detect(g, box);		if (!ret) return false;
	
	return true;
}

bool
Dect58Face::detectEye(cv::Mat& g, cv::Rect& box, cv::Point& eyeL, cv::Point& eyeR) {
	bool ret = false;

	Point tl = box.tl();
	Size sz = box.size();
	
	Rect roiL(tl + Point(box.width/2, 0), sz/2);
	Mat hL = g(roiL);
	Rect boxL;
	ret = dectEyeL.detect(hL, boxL);		if (!ret) return false;
	eyeL = boxL.tl()+roiL.tl() + Point(boxL.size()/2);
	
	Rect roiR(tl, sz/2);
	Mat hR = g(roiR);
	Rect boxR;
	ret = dectEyeR.detect(hR, boxR);		if (!ret) return false;
	eyeR = boxR.tl()+roiR.tl() + Point(boxR.size()/2);

	return true;
}
