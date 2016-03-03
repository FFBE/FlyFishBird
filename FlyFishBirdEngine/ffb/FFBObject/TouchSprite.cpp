//
//  TouchSprite.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TouchSprite.hpp"

namespace ffb {
    
    void TouchSprite::Clear()
    {
        TouchObject::Clear();
        m_touchScale = 1.15;
        m_touchSpriteFileName = "";
        m_sprite = FFBMalloc(Sprite);
        
    }
    
    void TouchSprite::Destory()
    {
        FFBSaveFree(m_sprite);
        TouchObject::Destory();
    }
    
    bool TouchSprite::Create()
    {
        if (!TouchObject::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool TouchSprite::Create(std::string fileName)
    {
        return Create(fileName, "");
    }
    
    bool TouchSprite::Create(std::string fileName, std::string touchFileName)
    {
        if (!TouchSprite::Create()) {
            return false;
        }
        
        m_sprite->Create(fileName);
        m_touchSpriteFileName = touchFileName;
        AddObject(m_sprite);
        
        m_touchSize = m_sprite->GetSize();
        
        return true;
    }
    
    bool TouchSprite::TouchShouldBegin(Touch *touch)
    {
        Point touchPoint = touch->ConverTouchPointToObject(this);
        if ((touchPoint.x<m_touchSize.width/2*m_sprite->GetScale().x &&
             touchPoint.x>-m_touchSize.width/2*m_sprite->GetScale().x) &&
            (touchPoint.y<m_touchSize.height/2*m_sprite->GetScale().y &&
             touchPoint.y>-m_touchSize.height/2*m_sprite->GetScale().x)) {
            
            float scale = GetScale().x;
            SetScale(GetScale().x*m_touchScale);
            m_touchScale = scale;
            
            if (m_touchSpriteFileName != "") {
                std::string fileName = m_sprite->GetFileName();
                m_sprite->Destory();
                m_sprite->Clear();
                m_sprite->Create(m_touchSpriteFileName);
                m_touchSpriteFileName = fileName;
            }
            
            m_isTouched = true;
            
            return true;
        }
        return false;
    }
    
    void TouchSprite::TouchMoved(ffb::Touch *touch){}
    
    void TouchSprite::TouchEnd(Touch * touch)
    {
        Point touchPoint = touch->ConverTouchPointToObject(this);
        float scale = GetScale().x/m_touchScale;
        SetScale(m_touchScale);
        m_touchScale = scale;
        
        if (m_touchSpriteFileName != "") {
            std::string fileName = m_sprite->GetFileName();
            m_sprite->Destory();
            m_sprite->Clear();
            m_sprite->Create(m_touchSpriteFileName);
            m_touchSpriteFileName = fileName;
        }
        
        m_isTouched = false;
        
        if ((touchPoint.x<m_touchSize.width/2*m_sprite->GetScale().x &&
             touchPoint.x>-m_touchSize.width/2*m_sprite->GetScale().x) &&
            (touchPoint.y<m_touchSize.height/2*m_sprite->GetScale().y &&
             touchPoint.y>-m_touchSize.height/2*m_sprite->GetScale().x)) {
                
            m_touchFunction(this);
        }
    }
    
    void TouchSprite::SetTouchScale(float touchScale)
    {
        if(m_isTouched)
        {
            m_sprite->SetScale(touchScale);
        }
        else
            m_touchScale = touchScale;
    }
    
    float TouchSprite::GetTouchScale()
    {
        return m_isTouched?GetScale().x/m_touchScale:m_touchScale;
    }
    
    void TouchSprite::SetTouchSpriteFileName(std::string fileName)
    {
        if (m_isTouched) {
            m_sprite->Destory();
            m_sprite->Clear();
            m_sprite->Create(fileName);
        }
        else
            m_touchSpriteFileName = fileName;
    }
    
    std::string TouchSprite::GetTouchSpriteFileName()
    {
        return m_isTouched?m_sprite->GetFileName():m_touchSpriteFileName;
    }
    
    Sprite * TouchSprite::GetSprite()
    {
        return m_sprite;
    }
    
}
