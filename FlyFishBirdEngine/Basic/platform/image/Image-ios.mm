//
//  Image-ios.m
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/9.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#import "Image.h"

#ifdef __APPLE__
#import <UIKit/UIImage.h>

ImageData GetImageData(const char * imageName)
{
    ImageData data = {0, 0, nullptr};
    
    CGImageRef image = [[UIImage alloc]initWithContentsOfFile:[[NSBundle mainBundle]pathForResource:[NSString stringWithUTF8String:imageName] ofType:nil]].CGImage;
    if (!image)
    {
        NSLog(@"failed to read image %s", imageName);
        return data;
    }
    
    data.width = CGImageGetWidth(image);
    data.height = CGImageGetHeight(image);
    data.data = (GLubyte *)malloc(sizeof(GLubyte) * data.width * data.height * 4);
    memset(data.data, 0, (data.width * data.height * 4));
    
    CGContextRef textureContext = CGBitmapContextCreate(data.data, data.width, data.height, 8, data.width*4, CGImageGetColorSpace(image), kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(textureContext, CGRectMake(0, 0, data.width, data.height), image);
    CGContextRelease(textureContext);
    
    return data;
}

void FreeImage(ImageData imagedata)
{
    imagedata.width = 0;
    imagedata.height = 0;
    if (imagedata.data != nullptr) {
        free(imagedata.data);
        imagedata.data = nullptr;
    }
}

#endif