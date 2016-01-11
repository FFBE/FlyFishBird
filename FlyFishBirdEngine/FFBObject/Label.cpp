//
//  Label.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/11.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Label.hpp"


namespace ffb {
    
    
    void Label::Clear()
    {
        Object::Clear();
    }
    
    bool Label::Create()
    {
        if (!Object::Create()) {
            return false;
        }
        
        return true;
    }
    
    
    bool Label::Create(std::string fontName, std::string text, float size)
    {
        if (!Object::Create()) {
            return false;
        }
        m_Texture = FFBMalloc(Texture2D);
        m_Texture->CreateStringTexture(fontName, text, size);
        
        return false;
    }
    
    void Label::Destory()
    {
        FontMgr::GetSingletonPtr()->DeleteFont(m_Texture->GetTextureHandle());
        m_Texture->release();
        Object::Destory();
    }
    
    
    
    void Label::SetString(std::string text)
    {
        m_Texture->SetString(text);
    }
    
    std::string Label::GetString()
    {
        return FontMgr::GetSingletonPtr()->GetText(m_Texture->GetTextureHandle());
    }
    
    
}
