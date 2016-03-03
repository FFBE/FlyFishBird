//
//  SelectSprite.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "SelectSprite.hpp"
#include "TouchSprite.hpp"


using namespace ffb;

void SelectSprite::Clear()
{
    TouchSprite::Clear();
}

void SelectSprite::Destory()
{
    TouchSprite::Destory();
}

bool SelectSprite::Create()
{
    if (!TouchSprite::Create()) {
        return false;
    }
    
    return true;
}


bool SelectSprite::Create(std::string filename)
{
    if (!TouchSprite::Create(filename)) {
        return false;
    }
    
    m_sprite->Destory();
    m_sprite->Clear();
    m_sprite->Create(filename, TextureWrapModelRepeat);
    AddObject(m_sprite);
    
    return true;
}

void SelectSprite::SetRepeatSize(float width, float height)
{
    SetRepeatSize(SizeMake(width, height));
}

void SelectSprite::SetRepeatSize(Size size)
{
    m_size = size;
    m_touchSize = m_size;
    Texture2D * m_texture = static_cast<Texture2D *>(m_sprite->GetRenderer());
    m_texture -> SetTextureScale(size.width/m_texture->GetSize().width, size.height/m_texture->GetSize().height);
}

Size SelectSprite::GetRepeatSize()
{
    return m_size;
}

