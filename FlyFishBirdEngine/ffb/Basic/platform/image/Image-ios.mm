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

long GetMin2PowerInImage(long number)
{
    int i = 1 << 1;
    while (number>i) {
        i = i << 1;
    }
    return i;
}

bool GetImageInfo(const char * imageName, unsigned char ** imageData, float * pWidth, float * pHeight, float * textureWidth, float * textureHeight)
{
    *imageData = nullptr;
    CGImageRef image = [UIImage imageNamed:[NSString stringWithUTF8String:imageName]].CGImage;
//    CGImageRef image = [[UIImage alloc]initWithContentsOfFile:[[NSBundle mainBundle]pathForResource:[NSString stringWithUTF8String:imageName] ofType:nil]].CGImage;
    if (!image)
    {
        NSLog(@"failed to read image %s", imageName);
        return false;
    }
    
    CGFloat width = CGImageGetWidth(image);
    CGFloat height = CGImageGetHeight(image);
    *pHeight = height;
    *pWidth = width;
    
    width = GetMin2PowerInImage(width);
    height = GetMin2PowerInImage(height);
    
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
    
    *textureHeight = height;
    *textureWidth = width;
    
    return true;
}


#endif