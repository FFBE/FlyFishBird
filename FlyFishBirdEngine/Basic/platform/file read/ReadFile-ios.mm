//
//  ReadFile.c
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/16.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "ReadFile.h"

#ifdef __APPLE__

#include <Foundation/NSBundle.h>

const char * ReadFile(const char * fileName)
{
    NSString * filePath = [[NSBundle mainBundle]pathForResource:[NSString stringWithUTF8String:fileName] ofType:nil];

    if (filePath == nil) {
        NSLog(@"failed to read file %s", fileName);
        
        return NULL;
    }
    NSString * fileContent = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:nil];
    
    return [fileContent cStringUsingEncoding:NSUTF8StringEncoding];
}

#endif
