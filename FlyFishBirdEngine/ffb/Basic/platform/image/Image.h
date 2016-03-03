//
//  Image.h
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/16.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Image_h
#define Image_h


#ifdef __cplusplus
extern "C"{
#endif


#include <stdio.h>
    
        
    bool GetImageInfo(const char * imageName, unsigned char ** imageData, float * width, float * height, float * textureWidth, float * textureHeight);


#ifdef __cplusplus
    }
#endif


#endif /* Image_h */
