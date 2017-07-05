//
//  main.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 13/9/15.
//
//

#include "Dect58.hpp"
#include "Detect.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58;

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	VideoCapture cap;
	cap.open(0);		if (!cap.isOpened()) return -1;
	int m1 = 640;
	int m2 = 480;
	cap.set(CV_CAP_PROP_FRAME_WIDTH,  m1);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, m2);
	const int n1 = 288;
	const int n2 = 288;
	Rect roi(Point((m1 - n1) / 2, (m2 - n2) / 2), Size(n1, n2));
	Mat f, g, h, w;
	Rect face;
	
	Detect detect;
	do {
		ret = cap.read(f);		if (!ret) continue;
		cvtColor(f, g, COLOR_BGR2GRAY);
		w = f.clone();
		
//		ret = detect.detect_roi(g, roi, face);
		ret = detect.detect(g, face);
		
		if (ret) {
			Dect58::show_rect(w, face, COLOR_0000FF);
			std::cout << face << std::endl;
		}
		else {
			Dect58::show_rect(w, roi, COLOR_FF0000);
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
