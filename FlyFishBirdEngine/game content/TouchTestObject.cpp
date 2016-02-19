//
//  TouchTestObject.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/11.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TouchTestObject.hpp"

bool TouchTestObject::Create()
{
    Object::Create();
    
    return true;
}


void TouchTestObject::Clear()
{
    Object::Clear();
}

void TouchTestObject::Destory()
{
    Object::Destory();
}

bool TouchTestObject::TouchShouldBegin(ffb::Point touchPoint)
{
    printf("%f %f\n", touchPoint.x, touchPoint.y);
    return true;
}

void TouchTestObject::TouchMoved(ffb::Point movePoint)
{
    printf("%f %f\n", movePoint.x, movePoint.y);
}

void TouchTestObject::TouchEnd(ffb::Point endPoint)
{
    printf("%f %f\n", endPoint.x, endPoint.y);
}