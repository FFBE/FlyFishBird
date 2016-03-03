//
//  SimpleFunction.h
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/26.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef SimpleFunction_h
#define SimpleFunction_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    
    
    void FloatToString(char *str, float f);
    float StringToFloat(char * str);
    
    void IntToString(char *str, int n);
    int StringToInt(char * str);
    
#ifdef __cplusplus
}
#endif

#endif /* SimpleFunction_h */
