//
//  Dect58Face.hpp
//  Dect58
//
//  Created by SIFEN ZHONG on 31/7/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Dect58Face_hpp
#define Dect58Face_hpp

#include "Dect58.hpp"
#include "Dect58UI.hpp"

const std::string FACE("haarcascade_frontalface_alt2.xml");
const std::string EYEL("haarcascade_mcs_lefteye_alt.xml");
const std::string EYER("haarcascade_mcs_righteye_alt.xml");

class Dect58Face {
	Dect58 dectFace;
	Dect58 dectEyeL;
	Dect58 dectEyeR;
	
public:
	Dect58Face() {
		dectFace.load(Dect58UI::CASCADES + FACE);
		dectEyeL.load(Dect58UI::CASCADES + EYEL);
		dectEyeR.load(Dect58UI::CASCADES + EYER);
	}

	bool detect(cv::Mat& g, cv::Rect& box);
};

#endif /* Dect58Face_hpp */
