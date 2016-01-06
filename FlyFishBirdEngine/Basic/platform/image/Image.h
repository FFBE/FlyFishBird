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


typedef struct __ImageData{
    
    float width;
    float height;
    
    unsigned char * data;
    
}ImageData;
    
        
    ImageData GetImageData(const char * imageName);

    void FreeImage(ImageData imagedata);


#ifdef __cplusplus
    }
#endif


#endif /* Image_h */
