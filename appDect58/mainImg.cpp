//
//  mainImg.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 25/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//
#include "Dect58.hpp"
#include "Dect58Face.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58UI;

std::string _imgfolder("/Users/zhongsifen/Work/Cert58/img/wcr/");

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
	Rect box;
	Point eyeL;
	Point eyeR;

	do {
		f = imread(_imgfolder + "2017-09-04-10-50-04-125.jpeg");
//		resize(f, w, f.size()*2);
		w = f.clone();
		imshow("Dect58", w);
		cvtColor(w, g, CV_BGR2GRAY);
		
		Dect58Face dect;
		
		ret = dect.detect(g, box);
		dect.detectEye(g, box, eyeL, eyeR);
		
		Cert58::align(w, eyeL, eyeR, h);
		
		if (ret) {
			Point pt(box.x + box.width/2, box.y + box.height/2);
			Dect58UI::show_point(w, pt, COLOR_0000FF);
			Dect58UI::show_rect(w, box, COLOR_0000FF);
			Dect58UI::show_point(w, eyeL, Scalar(0xF0, 0xF0, 0xF0));
			Dect58UI::show_point(w, eyeR, Scalar(0xF0, 0xF0, 0xF0));
			imshow("Dect58", w);
			imshow("align", h);
			imwrite(_imgfolder + "8.png", h);
		}
		key = waitKey();		if (key != 'r') break;
	} while (false);

	std::cout << "Hello, World!\n";
	return 0;
}
