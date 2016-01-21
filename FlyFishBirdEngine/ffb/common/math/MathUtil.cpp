//
//  MathUtil.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/4.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "MathUtil.hpp"
#include "Vector3.hpp"

#include <math.h>

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

float wrapPi(float theta)
{
    theta += kPi;
    theta -= floor(theta * k1over2Pi) * k2Pi;
    theta -= kPi;
    return theta;
}

float safeAcos(float x)
{
    if (x <= -1.0f) {
        return kPi;
    }
    if (x >= 1.0f) {
        return 0.0f;
    }
    
    return acos(x);
}



