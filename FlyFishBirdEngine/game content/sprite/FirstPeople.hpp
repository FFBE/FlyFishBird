//
//  FirstPeople.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/21.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef FirstPeople_hpp
#define FirstPeople_hpp

#include <stdio.h>
#include "People.hpp"

class FirstPeople:public People {
    
    
public:
    
    CreateClassFunctions(FirstPeople);
    bool Create(std::string fileName, float angle, float maxLength, float minLength);
    
};

#endif /* FirstPeople_hpp */
