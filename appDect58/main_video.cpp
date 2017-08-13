//
//  main_video.cpp
//  Dect58
//
//  Created by SIFEN ZHONG on 5/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Dect58.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58UI;

int main_video(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	Rect face;
	
		VideoCapture cap;
		cap.open(0);		if (!cap.isOpened()) return -1;
		cap.set(CV_CAP_PROP_FRAME_WIDTH,  640);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
		ret = cap.read(f);		if (!ret) return false;
		int m1 = f.cols;
		int m2 = f.rows;
		const int n1 = 288;
		const int n2 = 288;
		Rect roi(Point((m1 - n1) / 2, (m2 - n2) / 2), Size(n1, n2));
	
	Dect58::Dect58 detect(RES + "haarcascades_hand/palm.xml");
	do {
		key = 'q';

		ret = cap.read(f);		if (!ret) continue;
		w = f.clone();
		
		cvtColor(f, g, COLOR_BGR2GRAY);
		
		ret = detect.detect(g, face);
		
		if (ret) {
			Point pt(face.x + face.width/2, face.y + face.height/2);
			show_point(w, pt, COLOR_0000FF);
			show_rect(w, face, COLOR_0000FF);
			std::cout << pt << std::endl;
		}
		else {
			std::cout << "no face" << std::endl;
		}
		
		imshow("Dect58", w);
		key = waitKey(5);
		if (key == 'v') {
			std::cout << face.size() << std::endl;
		}
	} while (key != 'q');
	
	std::cout << "Hello, World!\n";
	return 0;
}

