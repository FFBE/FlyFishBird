//
//  TextureMgr.hpp
//  test1
//
//  Created by weitoo on 15/12/31.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#ifndef TextureMgr_hpp
#define TextureMgr_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Handle.hpp"
#include "Singleton.hpp"


namespace ffb {
    
    struct tagTexture{ };
    
    typedef Handle<tagTexture> HTexture;
    
    class TextureMgr:public Singleton<TextureMgr>
    {
        
    private:
        struct Texture
        {
            std::string m_Name;
            float m_Width;
            float m_Height;
            unsigned char * m_TextureData;
            
            bool Load (const std::string & name);
            void Unload();
        };
        
        typedef ffb::HandleMgr<Texture, HTexture> HTextureMgr;
        
        struct istring_less
        {
            bool operator () (const std::string& l, const std::string& r)const
            { return (::strcasecmp(l.c_str(), r.c_str()) < 0);}
        };
        
        typedef std::map <std::string, HTexture, istring_less> NameIndex;
        typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;
        
        HTextureMgr m_Textures;
        NameIndex m_NameIndex;
        
    public:
        
        TextureMgr() {}
        ~TextureMgr();
        
        HTexture GetTexture (const char * name);
        
        void    DeleteTexture(HTexture htex);
        
        
        const std::string& GetName(HTexture htex)const
        { return (m_Textures.Dereference(htex)->m_Name); }
        
        int GetWidth(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_Width; }
        
        int GetHeight(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_Height; }
        
        unsigned char * GetTextureData(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_TextureData; }
        
    };
    
    
    
    
    
    typedef Handle<tagTexture> HFont;
    
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


#endif /* TextureMgr_hpp */













