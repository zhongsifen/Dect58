//
//  Dect58Face.cpp
//  Dect58
//
//  Created by SIFEN ZHONG on 31/7/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Dect58Face.hpp"

bool
Dect58Face::detect(cv::Mat &g, cv::Rect &box) {
	bool ret = dectFace.detect(g, box);		if (!ret) return false;
	
	return true;
}
