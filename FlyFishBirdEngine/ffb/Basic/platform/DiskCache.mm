//
//  DiskCache.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "DiskCache.hpp"

#import <Foundation/Foundation.h>

namespace ffb {
    
    void DiskCache::CacheStringForKey(std::string string, std::string k)
    {
        NSUserDefaults * userDefault = [NSUserDefaults standardUserDefaults];
        NSString * str = [NSString stringWithFormat:@"%s", string.c_str()];
        NSString * key = [NSString stringWithFormat:@"%s", k.c_str()];
        
        [userDefault setObject:str forKey:key];
    }
    
    std::string DiskCache::GetStringForKey(std::string k)
    {
        NSString * key = [NSString stringWithFormat:@"%s", k.c_str()];
        NSString * str = [[NSUserDefaults standardUserDefaults]objectForKey:key];
        if (str == NULL) {
            return "";
        }
        return str.UTF8String;
    }
}