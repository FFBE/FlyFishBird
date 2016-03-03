//
//  RepeatSprite.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/29.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef RepeatSprite_hpp
#define RepeatSprite_hpp

#include <stdio.h>
#include "FlyFishBird.h"

namespace ffb {
    
    class RepeatSprite :public ffb::Sprite {
        
        
    public:
        
        CreateClassFunctions(RepeatSprite);
        
        bool Create(std::string fileName);
        
        void SetRepeatSize(Size size);
        void SetRepeatSize(float width, float height);
        Size GetRepeatSize();
        
    protected:
        
        Size m_size;
        
    };
    
}



#endif /* RepeatSprite_hpp */
