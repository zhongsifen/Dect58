//
//  main.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 13/9/15.
//
//

#define	FILEINPUT	0

#include "Dect58.hpp"
#include "Dect58Face.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58UI;

int main_(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
	Rect box;
	Point eyeL;
	Point eyeR;
	int level=0;
	double weight=0;
#if FILEINPUT
#else
	const int waittime = 1;
	VideoCapture cap;
	cap.open(0);		if (!cap.isOpened()) return -1;
	cap.set(CV_CAP_PROP_FRAME_WIDTH,  640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	ret = cap.read(f);		if (!ret) return -1;
	int m1 = f.cols;
	int m2 = f.rows;
	const int n1 = 288;
	const int n2 = 288;
	Rect roi(Point((m1 - n1) / 2, (m2 - n2) / 2), Size(n1, n2));
#endif
	
	do {
#if FILEINPUT
#else
		ret = cap.read(f);		if (!ret) continue;
#endif
		w = f.clone();
		
		Mat u(f.rows, f.cols, CV_32FC3);
		cvtColor(f, u, COLOR_BGR2HSV);
		split(u, hsl);
		g = hsl[2];

		Dect58Face dect;
		
		ret = dect.detect(g, box);
		dect.detectEye(g, box, eyeL, eyeR);
		
		if (ret) {
			Point pt(box.x + box.width/2, box.y + box.height/2);
			Dect58UI::show_point(w, pt, COLOR_0000FF);
			Dect58UI::show_rect(w, box, COLOR_0000FF);
			Dect58UI::show_point(w, eyeL, Scalar(0xF0, 0x00, 0xF0));
			Dect58UI::show_point(w, eyeR, Scalar(0x00, 0xF0, 0xF0));
			imshow("Dect58", w);
#if FILEINPUT
#endif
		}
		key = waitKey(waittime);		if (key == 'q') break;
	} while (1);
#if FILEINPUT
#endif
	std::cout << "Hello, World!\n";
	return 0;
}
