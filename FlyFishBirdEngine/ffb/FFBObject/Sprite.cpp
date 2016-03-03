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
        m_texture = FFBMalloc(Texture2D);
        m_touchEnable = false;
        Object::Clear();
    }
    
    void Sprite::Destory()
    {
        FFBSaveFree(m_texture);
        Object::Destory();
    }

    
    bool Sprite::Create()
    {
        return Object::Create();
    }
    
    bool Sprite::Create(const std::string &fileName)
    {
        return Create(fileName, TextureWrapModelClampToEdge);
    }
    
    bool Sprite::Create(const std::string  &fileName, TextureWrapModel model)
    {
        if (!Object::Create(m_texture)) {
            return false;
        }
        
        m_texture -> SetTextureWrapModel(model);
        
        if (!m_texture->CreateImageTexture(fileName))
        {
            m_texture->release();
            return false;
        }
        
        SetRenderer(m_texture);
        m_fileName = fileName;
        
        return true;
    }
    
    bool Sprite::CreateLaunchImageForApple()
    {
        m_texture = FFBMalloc(Texture2D);

        if (!Object::Create(m_texture)) {
            return false;
        }
        
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
                
        return true;
    }
    
    Size Sprite::GetSize()
    {
        return m_texture->GetSize();
    }
    
    std::string Sprite::GetFileName()
    {
        return m_fileName;
    }
    
//    std::string Sprite::CreateFileName(const std::string & fileName)
//    {
//        int scale = Device::GetSingleton().GetScreenScale();
//        
//        size_t index = fileName.find(".");
//        std::string fileHead = fileName.substr(0, index);
//        std::string fileType = fileName.substr(index);
//        
//        if (scale == 2.0)
//        {
//            return (fileHead + "@2x" + fileType) ;
//        }
//        else if (scale == 3.0)
//        {
//            return (fileHead + "@3x" + fileType) ;
//        }
//        else
//            return fileName;
//    }
    
}








