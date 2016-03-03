//
//  SimpleFunction.c
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/26.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "SimpleFunction.h"

void FloatToString(char *str, float f)
{
    sprintf(str, "%f", f);
}

float StringToFloat(char * str)
{
    float f;
    sscanf(str, "%f", &f);
    return f;
}

void IntToString(char *str, int n)
{
    sprintf(str, "%d", n);
}
int StringToInt(char * str)
{
    int n;
    sscanf(str, "%d", &n);
    return n;
}
