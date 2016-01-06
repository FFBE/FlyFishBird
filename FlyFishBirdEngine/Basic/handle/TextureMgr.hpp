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
#include <vector>
#include <map>
#include <string>
#include "Handle.cpp"
#include "HandleMgr.cpp"
#include "Singleton.hpp"
#include <OpenGLES/gltypes.h>


namespace ffb {
    
    struct tagTexture{ };
    
    typedef Handle<tagTexture> HTexture;
    
    class TextureMgr:public Singleton<TextureMgr> {
        
        struct Texture
        {
            
            std::string m_Name;
            unsigned int m_Width;
            unsigned int m_Height;
            GLubyte * m_TextureData;
            
            
            bool Load (const std::string & name);
            void Unload();
        };
        
        typedef HandleMgr<Texture, HTexture> HTextureMgr;
        
        struct istring_less
        {
            bool operator () (const std::string& l, const std::string& r)const
            { return (::strcasecmp(l.c_str(), r.c_str()) < 0);}
        };
        
    public:
        
        typedef std::map <std::string, HTexture, istring_less> NameIndex;
        typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;
        
        
        HTextureMgr m_Textures;
        NameIndex m_NameIndex;
        
        TextureMgr ( void ) {}
        ~TextureMgr ( void );
        
        
        HTexture GetTexture (const char * name);
        
        void    DeleteTexture(HTexture htex);
        
        
        const std::string& GetName(HTexture htex)const
        { return (m_Textures.Dereference(htex)->m_Name); }
        
        int GetWidth(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_Width; }
        
        int GetHeight(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_Height; }
        
        GLubyte * GetTextureData(HTexture htex) const
        { return m_Textures.Dereference(htex)->m_TextureData; }
        
    };
    
}


#endif /* TextureMgr_hpp */













