//
//  TouchLabel.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TouchLabel.hpp"

namespace ffb {
    
    void TouchLabel::Clear()
    {
        m_label = FFBMalloc(Label);

        m_touchScale = 1.15;
        m_touchText = "";
        m_touchColor = ColorMake(1, 0.3, 0.3, 1);
        TouchObject::Clear();
    }
    
    void TouchLabel::Destory()
    {
        FFBSaveFree(m_label);
        TouchObject::Destory();
    }
    
    bool TouchLabel::Create()
    {
        if (!TouchObject::Create()) {
            return false;
        }
        
        m_label->Create();
        AddObject(m_label);
        
        return true;
    }
    
    bool TouchLabel::Create(std::string text)
    {
        return Create(text, 17, "Helvetica");
    }
    
    bool TouchLabel::Create(std::string text, float size)
    {
        return Create(text, size, "Helvetica");
    }
    
    bool TouchLabel::Create(std::string text, float size, std::string fontName)
    {
        if (!TouchObject::Create()) {
            return false;
        }
        
        m_label -> Create(fontName, text, size);
        AddObject(m_label);
        
        return true;
    }
   
    
    bool TouchLabel::TouchShouldBegin(Touch * touch)
    {
        Point touchPoint = touch->ConverTouchPointToObject(this);
        
        if (touchPoint.x < m_label->GetSize().width/2 * m_label->GetScale().x   &&
            touchPoint.x > -m_label->GetSize().width/2 * m_label->GetScale().x  &&
            touchPoint.y < m_label->GetSize().height/2 * m_label->GetScale().x  &&
            touchPoint.y > -m_label->GetSize().height/2 * m_label->GetScale().x ) {
            
            float scale = GetScale().x;
            SetScale(GetScale().x*m_touchScale);
            m_touchScale = scale;
            
            Color color = m_label->GetTextColor();
            m_label->SetTextColor(m_touchColor);
            m_touchColor = color;
            
            if (m_touchText != "") {
                std::string text = m_label->GetText();
                m_label->SetText(m_touchText);
                m_touchText = text;
            }
            
            m_isTouched = true;
            
            return true;
        }
        return false;
    }
    
    void TouchLabel::TouchMoved(ffb::Touch *touch){}
    
    void TouchLabel::TouchEnd(Touch * touch)
    {
        Point touchPoint = touch->ConverTouchPointToObject(this);
        
        float scale = GetScale().x/m_touchScale;
        SetScale(m_touchScale);
        m_touchScale = scale;
        
        Color color = m_label->GetTextColor();
        m_label->SetTextColor(m_touchColor);
        m_touchColor = color;
        
        if (m_touchText != "") {
            std::string text = m_label->GetText();
            m_label->SetText(m_touchText);
            m_touchText = text;
        }
        
        m_isTouched = false;

        if (touchPoint.x < m_label->GetSize().width/2 * m_label->GetScale().x   &&
            touchPoint.x > -m_label->GetSize().width/2 * m_label->GetScale().x  &&
            touchPoint.y < m_label->GetSize().height/2 * m_label->GetScale().x  &&
            touchPoint.y > -m_label->GetSize().height/2 * m_label->GetScale().x ) {
            
            m_touchFunction(this);
        }
    }
    
    void TouchLabel::SetTouchScale(float touchScale)
    {
        if (m_isTouched) {
            m_label->SetScale(touchScale);
        }
        else
            m_touchScale = touchScale;
    }
    
    float TouchLabel::GetTouchScale()
    {
        return m_isTouched?GetScale().x/m_touchScale:m_touchScale;
    }
    
    void TouchLabel::SetTouchColor(Color touchColor)
    {
        if (m_isTouched) {
            m_label->SetTextColor(touchColor);
        }
        else
            m_touchColor = touchColor;
    }
    
    Color TouchLabel::GetTouchColor()
    {
        return m_isTouched?m_label->GetTextColor():m_touchColor;
    }
    
    void TouchLabel::SetTouchText(std::string text)
    {
        if (m_isTouched) {
            m_label->SetText(text);
        }
        else
            m_touchText = text;
    }
    
    std::string TouchLabel::GetTouchText()
    {
        return m_isTouched?m_label->GetText():m_touchText;
    }

    Label * TouchLabel::GetLabel()
    {
        return m_label;
    }
    
}