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

void getSimTransform(const Point2f pt_src[], const Point2f pt_dst[], Matx23d& aff)
{
	Point2f s = pt_src[1] - pt_src[0];
	Point2f d = pt_dst[1] - pt_dst[0];
	double s_norm = norm(s);
	double d_norm = norm(d);
	double alpha = d_norm / s_norm;
	
	double cs = (Mat(s).dot(Mat(d)))/(s_norm*d_norm);
	double sn = sqrt(1 - cs*cs);
	
	cs *= alpha;
	sn *= alpha;
	
	Point2f s0 = pt_src[0];
	Point2f d0 = pt_dst[0];
	
	Point2f b = d0 - Point2f((float)(+cs*s0.x +sn*s0.y), (float)(-sn*s0.x +cs*s0.y));
	
	aff = Matx23d(+cs, +sn, b.x, -sn, +cs, b.y);
}

bool
Cert58::align(cv::Mat& f, cv::Point& eyeL, cv::Point& eyeR, cv::Mat& h) {
	const Point2f pt_src[2] = { Point2f(eyeL), Point2f(eyeR)};
	const Point2f pt_dst[2] = { Point2f(_eyeL), Point2f(_eyeR)};
	Matx23d aff;
	getSimTransform(pt_src, pt_dst, aff);
	warpAffine(f, h, aff, _box);
	
	return true;
}
