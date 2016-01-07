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

bool GetFontInfo(const char * text,const char * fontName, float size, unsigned char ** fontData, float * width, float * height)
{
    NSString * string = [NSString stringWithUTF8String:text] ;
    UIFont * font = [UIFont fontWithName:[NSString stringWithUTF8String:fontName] size:size];
    CGSize boundingSize = CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX);
    CGSize dimensions = [string  sizeWithFont:font
                                 constrainedToSize:boundingSize
                                 lineBreakMode:NSLineBreakByWordWrapping];
        
    NSUInteger textureWidth  = nextpot(dimensions.width);
    NSUInteger textureHeight = nextpot(dimensions.height);
    *fontData = (unsigned char *)malloc(textureHeight*textureWidth*2);
    
    CGContextRef context = CGBitmapContextCreate(*fontData, textureWidth, textureHeight, 8, textureWidth, CGColorSpaceCreateDeviceGray(), kCGImageAlphaNone);
    if(!context)
    {
        if(*fontData == NULL)
        {
            free(*fontData);
        }
        return false;
    }
    
    CGContextSetGrayFillColor(context, 1.0f, 1.0f);
    CGContextTranslateCTM(context, 0.0f, textureHeight);
    CGContextScaleCTM(context, 1.0f, -1.0f);
    UIGraphicsPushContext(context);

    CGSize drawSize = [string sizeWithFont:font constrainedToSize:dimensions lineBreakMode:NSLineBreakByWordWrapping];
    CGRect drawArea = CGRectMake(0, (dimensions.height - drawSize.height) / 2, dimensions.width, drawSize.height);
    [string drawInRect:drawArea withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:NSTextAlignmentCenter];
    UIGraphicsPopContext();
    CGContextRelease(context);
    
    return true;
}

void GetFontInfoWithLimit(char * text, char * fontName, float size, float limitWidth,unsigned char ** fontData, float * width, float * height)
{
    
}

#endif