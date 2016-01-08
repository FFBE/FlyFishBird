//
//  FontMgr.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/7.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "FontMgr.hpp"
#include "Font.h"

namespace ffb {
    
    FontMgr::~FontMgr()
    {
        FontMap::iterator i, begin = m_FontMap.begin(), end = m_FontMap.end();
        for (i = begin; i != end; i ++) {
            m_Fonts.Dereference(i->second)->UnLoad();
        }
    }
    
    HFont FontMgr::GetFont(std::string name, std::string text, float fontSize)
    {
        ++m_FontId;
        FontMapInsertRc rc = m_FontMap.insert(std::make_pair(m_FontId, HFont()));
        if (rc.second) {
            Font* font = m_Fonts.Acquire(rc.first->second);
            if (!font->Load(name, text, fontSize))
            {
                DeleteFont(rc.first->second);
                rc.first->second = HFont();
            }
        }
        
        return rc.first->second;
    }
    
    void FontMgr::SetText(HFont hfont, std::string text)
    {
        m_Fonts.Dereference(hfont)->SetText(text);
    }
    
    void FontMgr::SetFontName(HFont hfont, std::string fontName)
    {
        m_Fonts.Dereference(hfont)->SetFontName(fontName);
    }
    
    void FontMgr::SetFontSize(HFont hfont, float size)
    {
        m_Fonts.Dereference(hfont)->SetFontSize(size);
    }
    
    void FontMgr::DeleteFont(HFont hfont)
    {
        Font * font = m_Fonts.Dereference(hfont);
        if (font != 0)
        {
            m_FontMap.erase(m_FontMap.find(hfont));
            
            font->UnLoad();
            m_Fonts.Release(hfont);
        }
    }
    
    bool FontMgr::Font::Load(std::string name, std::string text, float fontSize)
    {
        m_FontName = name;
        m_Text = text;
        m_FontSize = fontSize;
        m_FontData = nullptr;
        
        return GetFontInfo(m_Text.c_str(), m_FontName.c_str(), m_FontSize, &m_FontData, &m_Width, &m_Height);
    }
    
    void FontMgr::Font::SetText(std::string text)
    {
        m_Text = text;
        GetFontInfo(m_Text.c_str(), m_FontName.c_str(), m_FontSize, &m_FontData, &m_Width, &m_Height);
    }
    
    void FontMgr::Font::SetFontName(std::string fontName)
    {
        m_FontName = fontName;
        GetFontInfo(m_Text.c_str(), m_FontName.c_str(), m_FontSize, &m_FontData, &m_Width, &m_Height);
    }
    
    void FontMgr::Font::SetFontSize(float size)
    {
        m_FontSize = size;
        GetFontInfo(m_Text.c_str(), m_FontName.c_str(), m_FontSize, &m_FontData, &m_Width, &m_Height);
    }
    
    void FontMgr::Font::UnLoad()
    {
        m_FontName.erase();
        m_Text.erase();
        if (m_FontData != nullptr) {
            free(m_FontData);
            m_FontData = nullptr;
        }
    }
}

