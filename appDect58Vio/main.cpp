//
//  main.cpp
//  appDect58
//
//  Created by SIFEN ZHONG on 13/9/15.
//
//

#include "_opencv2.hpp"
#include "Dect58.hpp"
#include <iostream>
using namespace cv;
using namespace Dect58;

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, g, h, w;
	Rect face;
	VideoCapture cap;
	cap.open(0);		if (!cap.isOpened()) return -1;
	cap.set(CV_CAP_PROP_FRAME_WIDTH,  640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	ret = cap.read(f);		if (!ret) return false;
	
	do {
		ret = cap.read(f);		if (!ret) continue;
		w = f.clone();
		
		
		imshow("Dect58", w);
		key = waitKey(5);
		if (key == 'v') {
			std::cout << face.size() << std::endl;
		}
	} while (key != 'q');
	
	std::cout << "Hello, World!\n";
	return 0;
}
