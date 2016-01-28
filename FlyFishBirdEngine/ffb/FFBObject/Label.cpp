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
    
    bool Label::Create(const std::string &text)
    {
        return Create("Helvetica", text, 17);
    }
    
    bool Label::Create(const std::string &text, float fontSize)
    {
        return Create("Helvetica", text, fontSize);
    }
    
    bool Label::Create(const std::string &fontName,const std::string & text, float size)
    {
        m_Texture = FFBMalloc(Texture2D);
        if (!m_Texture->CreateStringTexture(fontName, text, size))
        {
            m_Texture->release();
            return false;
        }
        
        m_fontName = fontName;
        m_text = text;
        m_fontName = size;
        
        SetRenderer(m_Texture);
        
        return true;
    }
    
    void Label::SetText(const std::string &text)
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
