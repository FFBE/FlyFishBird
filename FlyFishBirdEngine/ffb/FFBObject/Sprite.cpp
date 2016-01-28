//
//  Sprite.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Sprite.hpp"
#include "Device.hpp"

namespace ffb {
    
    
    void Sprite::Clear()
    {
        Object::Clear();
    }
    
    bool Sprite::Create()
    {
        return Object::Create();
    }
    
    bool Sprite::Create(const std::string &fileName)
    {
        if (!Object::Create()) {
            return false;
        }
        
        m_texture = FFBMalloc(Texture2D);
        if (!m_texture->CreateImageTexture(CreateFileName(fileName)))
        {
            m_texture->release();
            return false;
        }
        
        SetRenderer(m_texture);
        
        return true;
    }
    
    bool Sprite::CreateLaunchImageForApple()
    {
        if (!Object::Create()) {
            return false;
        }
        
        m_texture = FFBMalloc(Texture2D);
        
        bool createSuccess = false;
        
        float scale = Device::GetSingletonPtr()->GetScreenScale();
        float width = Device::GetSingletonPtr()->GetScreenWidth();
        
        if (scale == 2 && width == 480) {
            createSuccess = m_texture -> CreateImageTexture("LaunchImage@2x.png");
        }
        else if (scale == 2 && width == 568)
        {
            createSuccess = m_texture -> CreateImageTexture("LaunchImage-568@2x.png");
        }
        else if (scale == 3)
        {
            createSuccess = m_texture -> CreateImageTexture("LaunchImage@3x.png");
        }
        
        if (! createSuccess)
        {
            m_texture->release();
            return false;
        }
        
        SetRenderer(m_texture);
        
        return true;
    }
    
    void Sprite::Destory()
    {
        m_texture->release();
        Object::Destory();
    }
    
    
    
    std::string Sprite::CreateFileName(const std::string & fileName)
    {
        int scale = Device::GetSingleton().GetScreenScale();
        
        size_t index = fileName.find(".");
        std::string fileHead = fileName.substr(0, index);
        std::string fileType = fileName.substr(fileName.length()-index);
        if (scale == 2.0)
        {
            return (fileHead + "@2x" + fileType) ;
        }
        else if (scale == 3.0)
        {
            return (fileHead + "@3x" + fileType) ;
        }
        else
            return fileName;
    }
    
}








