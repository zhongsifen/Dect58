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
// (26, 44)
//          (178, 196)
// (26 + 178)/2 = 102 - 64 = 38
// (44 + 196)/2 = 120 - 64 = 56

// 178 - 26 = 152
// 196 - 44 = 152

// (74, 98)  (130, 96)
// 130 - 74 = 56

// 128: center: 64,  L: 64-28 = 36, R: 64+28 = 92;  (36, 92) -> (18, 46)
// 102 -> 64    L: 102-64 = 38, R: 102+64 = 166

// (102, 120)
// (102,  98)
//  98 - 56 = 42
// (102, 136)

// (36, 42) (92, 42)


namespace Cert58 {
	const cv::Point _eyeL(92, 42);
	const cv::Point _eyeR(36, 42);
	const cv::Size _box(128, 128);
	
	bool align(cv::Mat& f, cv::Point& eyeL, cv::Point& eyeR, cv::Mat& h);
}

const std::string FACE("haarcascade_frontalface_alt2.xml");
const std::string EYEL("haarcascade_lefteye_2splits.xml");
//const std::string EYEL("haarcascade_mcs_lefteye_alt.xml");
const std::string EYER("haarcascade_righteye_2splits.xml");
//const std::string EYER("haarcascade_mcs_righteye_alt.xml");

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
	bool detectEye(cv::Mat& g, cv::Rect& box, cv::Point& eyeL, cv::Point& eyeR);
};

#endif /* Dect58Face_hpp */
