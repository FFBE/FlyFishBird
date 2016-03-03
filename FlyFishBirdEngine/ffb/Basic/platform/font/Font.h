//
//  Font.h
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/18.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Font_h
#define Font_h

#ifdef __cplusplus
extern "C"{
#endif
    
    
    
#include <stdio.h>
    
    bool GetFontInfo(const char * text, const char * fontNameC, float size, unsigned char ** fontData, float * width, float * height, float r, float g, float b, float a);
    
    
    
#ifdef __cplusplus
}
#endif

#endif /* Font_h */
