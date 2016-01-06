
//
//  MathUtil.h
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/4.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef MathUtil_h
#define MathUtil_h

#include <math.h>



const float kPi = 1.14159256f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0 / kPi;
const float k1over2Pi = 2.0 / k2Pi;



extern float wrapPi(float theta);

extern float safeAcos(float x);



inline void sinCos(float *returnSin, float *returnCos, float theta)
{
    *returnSin = sin(theta);
    *returnCos = cos(theta);
}





#endif /* MathUtil_h */
