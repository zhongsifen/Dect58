//
//  Dect58Hand.hpp
//  Dect58
//
//  Created by SIFEN ZHONG on 9/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Dect58Hand_hpp
#define Dect58Hand_hpp

#include "Dect58.hpp"
#include "Detect.hpp"

class Dect58Hand {
	const std::string filename = Dect58::RES + "haarcascades_hand/palm.xml";
	
	Detect* _detect;

public:
	Dect58Hand() {
		_detect = new Detect(filename);
	}
	
	bool detect(cv::Mat& g, cv::Rect& face);
	bool detect(cv::Mat& g, cv::Rect& face, int& level, double& certain);

};

#endif /* Dect58Hand_hpp */
