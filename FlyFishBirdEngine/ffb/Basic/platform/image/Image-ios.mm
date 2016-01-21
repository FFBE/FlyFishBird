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

bool GetImageInfo(const char * imageName, unsigned char ** imageData, float * pHeight, float * pWidth)
{
    *imageData = nullptr;
    CGImageRef image = [[UIImage alloc]initWithContentsOfFile:[[NSBundle mainBundle]pathForResource:[NSString stringWithUTF8String:imageName] ofType:nil]].CGImage;
    if (!image)
    {
        NSLog(@"failed to read image %s", imageName);
        return false;
    }
    
    CGFloat width = CGImageGetWidth(image);
    CGFloat height = CGImageGetHeight(image);
    
    *imageData = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 4);
    memset(*imageData, 0, width*height*4);
    
    CGContextRef textureContext = CGBitmapContextCreate(*imageData, width, height, 8, width*4, CGImageGetColorSpace(image), kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(textureContext, CGRectMake(0, 0, width, height), image);
    CGContextRelease(textureContext);
    
    if (!textureContext) {
        if (*imageData != NULL) {
            free(*imageData);
        }
    }
    
    *pHeight = height;
    *pWidth = width;
    
    return true;
}


#endif