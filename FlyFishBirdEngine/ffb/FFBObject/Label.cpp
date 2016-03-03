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
        m_Texture = FFBMalloc(Texture2D);
        m_touchEnable = false;
        Object::Clear();
    }
    
    void Label::Destory()
    {
        FFBSaveFree(m_Texture);
        Object::Destory();
    }

    bool Label::Create()
    {
        return Create("Helvetica", "", 17);
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
        if (!m_Texture->CreateStringTexture(fontName, text, size, ColorMake(1, 1, 1, 1)))
        {
            m_Texture->release();
            return false;
        }
        
        m_fontName = fontName;
        m_text = text;
        m_fontSize = size;
        m_textColor = ColorMake(1, 1, 1, 1);
        m_size = m_Texture->GetSize();
        
        SetRenderer(m_Texture);
        
        return true;
    }
    
    void Label::SetText(const std::string &text)
    {
        m_text = text;
        m_Texture->Destory();
        m_Texture->Clear();
        m_Texture->CreateStringTexture(m_fontName, m_text, m_fontSize, m_textColor);
        m_size = m_Texture->GetSize();
    }
    
    void Label::SetTextColor(Color color)
    {
        SetTextColor(color.r, color.g, color.b, color.a);
    }
    
    void Label::SetTextColor(float r, float g, float b, float a)
    {
        m_textColor = ColorMake(r, g, b, a);
        m_Texture->Destory();
        m_Texture->Clear();
        m_Texture->CreateStringTexture(m_fontName, m_text, m_fontSize, m_textColor);
    }
    
    Color Label::GetTextColor()
    {
        return m_textColor;
    }
    
    std::string Label::GetText()
    {
        return m_text;
    }

    Size Label::GetSize()
    {
        return m_size;
    }
    
}
