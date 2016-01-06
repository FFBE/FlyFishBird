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
    
    
    typedef struct {
        float width;
        float height;
        char * text;
        unsigned int length;
        float * data;
        char * fontName;
        float size;
    }Font;
    
    
    Font GetFontData(char * text, char * fontName, float size, float width);
    
    
#ifdef __cplusplus
}
#endif

#endif /* Font_h */
