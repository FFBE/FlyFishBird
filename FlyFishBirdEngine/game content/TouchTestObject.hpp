//
//  TouchTestObject.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/11.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef TouchTestObject_hpp
#define TouchTestObject_hpp

#include <stdio.h>
#include "FlyFishBird.h"

class TouchTestObject:public ffb::Object {
    
    

public:
    
    CreateClassFunctions(TouchTestObject);
    
    virtual bool TouchShouldBegin( ffb::Point touchPoint );
    virtual void TouchMoved(ffb::Point movePoint);
    virtual void TouchEnd(ffb::Point endPoint);
    
};

#endif /* TouchTestObject_hpp */
