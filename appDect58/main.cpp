//
//  main.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 13/9/15.
//
//

#define	FILEINPUT	1

#include "Dect58.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58UI;

int main(int argc, const char * argv[]) {
	//	Dect58 dect(RES + "haarcascades/haarcascade_frontalface_alt2.xml");
	Dect58 dect(RES + "haarcascades_hand/palm.xml");
	
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
	Rect box;
	int level=0;
	double weight=0;
#if FILEINPUT
	const int waittime = 0;
	int i = 1;
	std::string folder = Dect58UI::HAND;
	std::string name = "B-train";
	std::string index = "001";
	std::string postfix = ".ppm";
	std::string filename;
	std::string rectname = "B-rect";
	std::ofstream positive(folder + "positive.txt");		if (!positive.is_open()) return -1;
#else
	const int waittime = 5;
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
#endif
	do {
#if FILEINPUT
		char index_c[4];
		snprintf(index_c, 4, "%03d", i++);
		filename = name + index_c + postfix;
		f = imread(folder + filename);	if (f.data == nullptr) break;
#else
		ret = cap.read(f);		if (!ret) continue;
#endif
		w = f.clone();
		
		Mat u(f.rows, f.cols, CV_32FC3);
		cvtColor(f, u, COLOR_BGR2HSV);
		split(u, hsl);
		g = hsl[2];
		
		ret = dect.detect(g, box, level, weight);
		
		if (ret) {
			Point pt(box.x + box.width/2, box.y + box.height/2);
			Dect58UI::show_point(w, pt, COLOR_0000FF);
			Dect58UI::show_rect(w, box, COLOR_0000FF);
			std::cout << "level: " << level << "  " << "weight: " << weight << std::endl;
			imshow("Dect58", w);
#if FILEINPUT
			imwrite(folder + rectname + index_c + ".png", w);
			positive << filename;
			positive << std::endl;
#endif
		}
		key = waitKey(waittime);		if (key == 'q') break;
	} while (1);
#if FILEINPUT
	positive.close();
#endif
	std::cout << "Hello, World!\n";
	return 0;
}
