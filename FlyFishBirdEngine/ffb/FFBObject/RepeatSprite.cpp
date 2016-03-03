//
//  Pillar.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/29.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "RepeatSprite.hpp"

namespace ffb {
    
    CreateSimpleClass(RepeatSprite, Sprite);
    
    
    bool RepeatSprite::Create(std::string fileName)
    {
        if (!Sprite::Create(fileName, TextureWrapModelRepeat)) {
            return false;
        }
        
        return true;
    }
    
    void RepeatSprite::SetRepeatSize(float width, float height)
    {
        SetRepeatSize(SizeMake(width, height));
    }
    
    void RepeatSprite::SetRepeatSize(Size size)
    {
        m_size = size;
        
        m_texture -> SetTextureScale(size.width/m_texture->GetSize().width, size.height/m_texture->GetSize().height);
    }
    
    Size RepeatSprite::GetRepeatSize()
    {
        return m_size;
    }
    
}




