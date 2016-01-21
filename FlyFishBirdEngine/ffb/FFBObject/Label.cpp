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
        m_fontName = fontName;
        m_text = text;
        m_fontName = size;
        
        return false;
    }
    
    void Label::SetText(std::string text)
    {
        m_text = text;
        m_Texture->Destory();
        m_Texture->CreateStringTexture(m_fontName, m_text, m_fontSize);
    }
    
    void Label::SetColor(float r, float g, float b)
    {
        
    }
    
    std::string Label::GetText()
    {
        return m_text;
    }
    
    void Label::Destory()
    {
        
        Object::Destory();
    }
    

    
    
}
