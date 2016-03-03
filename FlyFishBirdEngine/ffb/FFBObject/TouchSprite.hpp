//
//  ClickSprite.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef ClickSprite_hpp
#define ClickSprite_hpp

#include <stdio.h>
#include "TouchObject.hpp"
#include "Sprite.hpp"

namespace ffb {
    
    
    class TouchSprite: public TouchObject {
        
        
    public:
        
        CreateClassFunctions(TouchSprite);
        
        bool Create(std::string fileName);
        bool Create(std::string fileName, std::string touchFileName);
        
        void SetTouchScale(float touchScale);
        float GetTouchScale();
                
        TouchEventFuncation;
        
        void SetTouchSpriteFileName(std::string fileName);
        std::string GetTouchSpriteFileName();
        
        Sprite * GetSprite();
        
    protected:
                        
        float               m_touchScale;
        
        std::string         m_touchSpriteFileName;
        Sprite *            m_sprite;
        
        Size                m_touchSize;
    };
    
}

#endif /* ClickSprite_hpp */
