//
//  main.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 13/9/15.
//
//

#include "Dect58.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58UI;

int main_file(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
	Rect box;
	int level=0;
	double weight=0;
	
	std::string folder = Dect58UI::HAND;
 	std::string name = "B-train";
	std::string index = "001";
	std::string postfix = ".ppm";
	std::string filename;
	
	std::string rectname = "B-rect";
	
	std::ofstream positive(folder + "positive.txt");		if (!positive.is_open()) return -1;
	
	Dect58 dect(RES + "haarcascades_hand/palm.xml");
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
		
		ret = dect.detect(g, box, level, weight);
		
		if (ret) {
			Point pt(box.x + box.width/2, box.y + box.height/2);
			Dect58UI::show_point(w, pt, COLOR_0000FF);
			Dect58UI::show_rect(w, box, COLOR_0000FF);
			imwrite(folder + rectname + index_c + ".png", w);
			positive << filename;
			positive << std::endl;
			std::cout << "level: " << level << "  " << "weight: " << weight << std::endl;
			
			imshow("Dect58", w);
		}
		key = waitKey();		if (key == 'q') break;
	} while (1);
	
	positive.close();
	
	std::cout << "Hello, World!\n";
	return 0;
}
