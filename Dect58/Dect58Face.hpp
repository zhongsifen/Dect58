//
//  Dect58Face.hpp
//  Dect58
//
//  Created by SIFEN ZHONG on 31/7/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Dect58Face_hpp
#define Dect58Face_hpp

#include "Detect.hpp"

class Dect58Face {
	Detect* detect;
	
	Dect58Face() {
		this->detect = new Detect();
	}
};

#endif /* Dect58Face_hpp */
