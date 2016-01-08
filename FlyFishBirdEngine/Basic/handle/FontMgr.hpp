//
//  FontMgr.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/7.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef FontMgr_hpp
#define FontMgr_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Handle.hpp"
#include "Singleton.hpp"

namespace ffb {
    
    struct tagFont{};
    
    typedef Handle<tagFont> HFont;
    
    class FontMgr: public Singleton<FontMgr>
    {
        
    private:
        
        struct Font
        {
            float m_Width;
            float m_Height;
            unsigned char * m_FontData;
            float m_FontSize;
            std::string m_Text;
            std::string m_FontName;
            
            bool Load(std::string fontName, std::string text, float fontSize);
            void SetText(std::string text);
            void SetFontSize(float size);
            void SetFontName(std::string fontName);
            void UnLoad();
        };
                
        typedef HandleMgr<Font, HFont> HFontMgr;
        
        typedef std::map <unsigned int , HFont> FontMap;
        typedef std::pair <FontMap::iterator, bool> FontMapInsertRc;
        
        HFontMgr m_Fonts;
        FontMap m_FontMap;
        
        unsigned int m_FontId;
        
    public:
        
        FontMgr() { m_FontId = 0; }
        ~FontMgr();
        
        HFont GetFont(std::string fontName, std::string text, float fontSize);
        
        void SetText(HFont hfont, std::string text);
        void SetFontSize(HFont hfont, float size);
        void SetFontName(HFont hfont, std::string fontName);
        
        void DeleteFont(HFont hfont);
        
        float GetWidth(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_Width; }
        
        float GetHeight(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_Height; }
        
        float GetFontSize(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_FontSize; }
        
        unsigned char * GetFontData(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_FontData; }
        
        std::string GetText(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_Text; }
        
        std::string GetFontName(HFont hfont) const
        { return m_Fonts.Dereference(hfont)->m_FontName; }
        
    };
    
}





#endif /* FontMgr_hpp */
