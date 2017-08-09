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
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
	Rect face;
	
	std::string folder = Dect58::HAND;
 	std::string name = "B-train";
	std::string index = "001";
	std::string postfix = ".ppm";
	std::string filename;
	
	std::string rectname = "B-rect";
	
	std::ofstream positive(folder + "positive.txt");		if (!positive.is_open()) return -1;
	
	Detect detect(Dect58::RES + "haarcascades_hand/palm.xml");
	int i = 1;
	do {
		char index_c[4];
		snprintf(index_c, 4, "%03d", i++);
		filename = name + index_c + postfix;
		f = imread(folder + filename);	if (f.data == nullptr) break;
		w = f.clone();
		
		Mat u(f.rows, f.cols, CV_32FC3);
		cvtColor(f, u, COLOR_BGR2HSV);
		split(u, hsl);
		g = hsl[2];
		
//		cvtColor(f, g, COLOR_BGR2GRAY);
		
//		imshow("Dect58", f);
//		imshow("0", hsl[0]);
//		imshow("1", hsl[1]);
//		imshow("2", hsl[2]);
//		key = waitKey();
		
		ret = detect.detect(g, face);
		
		if (ret) {
			Point pt(face.x + face.width/2, face.y + face.height/2);
			Dect58::show_point(w, pt, COLOR_0000FF);
			Dect58::show_rect(w, face, COLOR_0000FF);
			imwrite(folder + rectname + index_c + ".png", w);
			positive << filename;
			positive << std::endl;
			imshow("Dect58", w);
			key = waitKey(5);
		}
//		else {
//			std::cout << "no face" << std::endl;
//		}
//		
//		imshow("Dect58", w);
//		key = waitKey(5);
//		if (key == 'v') {
//			std::cout << face.size() << std::endl;
//		}
	} while (1);
	
	positive.close();
	
	std::cout << "Hello, World!\n";
	return 0;
}
