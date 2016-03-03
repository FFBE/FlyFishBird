//
//  DiskCache.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef DiskCache_hpp
#define DiskCache_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include <string>

namespace ffb {
    
    class DiskCache: public Singleton<DiskCache>  {
        
        
    public:
        
        void CacheStringForKey(std::string string,std::string k);
        std::string GetStringForKey(std::string k);
    };
    
}


#endif /* DiskCache_hpp */
