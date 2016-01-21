//
//  Font.c
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/18.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Font.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <UIKit/UIKit.h>
#include <CoreText/CoreText.h>
#include "GameController.hpp"

unsigned long nextpot(unsigned long x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

bool GetFontInfo(const char * text,const char * fontNameC, float size, unsigned char ** fontData, float * width, float * height)
{
    NSString * string = [NSString stringWithUTF8String:text] ;
    NSString * fontName = [NSString stringWithUTF8String:fontNameC];
    UIFont * font = [UIFont fontWithName:fontName size:size*[UIScreen mainScreen].scale];
    if(!font)
    {
        NSLog(@"未找到相关字体信息：%@", fontName);
    }
    
    CGSize boundingSize = CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX);
    CGSize dimensions = [string boundingRectWithSize:boundingSize options:NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName:font} context:nil].size;

    *fontData = (unsigned char *)malloc(dimensions.height*dimensions.width*4);
    memset(*fontData, 0, dimensions.height*dimensions.width*4);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(*fontData, dimensions.width, dimensions.height, 8, dimensions.width*4, colorSpace, kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(colorSpace);
    
    if(!context)
    {
        NSLog(@"获取字体纹理上下文失败");
        if(*fontData == NULL)
        {
            free(*fontData);
        }
        return false;
    }
    
    CGContextSetRGBFillColor(context, 0, 0, 0, 1);
    CGContextTranslateCTM(context, 0.0f, dimensions.height);
    CGContextScaleCTM(context, 1.0f, -1.0f);
    
    UIGraphicsPushContext(context);
    
    CGSize drawSize = [string boundingRectWithSize:dimensions options:NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName:font} context:nil].size;
    CGRect drawArea = CGRectMake(0, (dimensions.height - drawSize.height) / 2, dimensions.width, drawSize.height);
    
    [string drawInRect:drawArea withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:NSTextAlignmentLeft];
    
    UIGraphicsPopContext();
    CGContextRelease(context);
    
    *width = dimensions.width;
    *height = dimensions.height;
        
    return true;
}

void GetFontInfoWithLimit(char * text, char * fontName, float size, float limitWidth,unsigned char ** fontData, float * width, float * height)
{
    
}

#endif