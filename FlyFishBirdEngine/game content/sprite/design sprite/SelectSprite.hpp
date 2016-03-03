//
//  SelectSprite.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef SelectSprite_hpp
#define SelectSprite_hpp

#include <stdio.h>
#include "FlyFishBird.h"

class SelectSprite:public ffb::TouchSprite {
    
public:
    
    CreateClassFunctions(SelectSprite);
    bool Create(std::string filename);
    
    void SetRepeatSize(ffb::Size size);
    void SetRepeatSize(float width, float height);
    ffb::Size GetRepeatSize();
    
private:
            
    
    ffb::Size m_size;
    
};

#endif /* SelectSprite_hpp */
