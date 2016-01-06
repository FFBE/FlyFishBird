//
//  TextureMgr.cpp
//  test1
//
//  Created by weitoo on 15/12/31.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#include "TextureMgr.hpp"
#include "Image.h"
#include <cassert>
#include <iostream>


namespace ffb {
    TextureMgr::~TextureMgr()
    {
        NameIndex::iterator i, begin = m_NameIndex.begin(), end = m_NameIndex.end();
        for (i = begin; i!= end; ++i)
        {
            m_Textures.Dereference(i->second)->Unload();
        }
    }
    
    HTexture TextureMgr::GetTexture(const char *name)
    {
        NameIndexInsertRc rc = m_NameIndex.insert(std::make_pair(name, HTexture()));//如果存在，second为false，如果不存在，second为true
        if (rc.second)
        {
            Texture* tex = m_Textures.Acquire(rc.first->second);
            if (!tex->Load(rc.first->first))
            {
                DeleteTexture(rc.first->second);
                rc.first->second = HTexture();
            }
        }
        
        return rc.first->second;
    }
    
    void TextureMgr::DeleteTexture(HTexture htex)
    {
        Texture* tex = m_Textures.Dereference(htex);
        if (tex != 0)
        {
            m_NameIndex.erase(m_NameIndex.find(tex->m_Name));
            
            tex->Unload();
            m_Textures.Release(htex);
        }
    }
    
    bool TextureMgr::Texture::Load(const std::string &name)
    {
        m_Name = name;
        
        //...从文件系统载入材质，失败是返回false
        ImageData imageData = GetImageData(name.c_str());
        if (imageData.data == nullptr)
        {
            return false;
        }
        
        m_Width = imageData.width;
        m_Height = imageData.height;
        
        m_TextureData = (GLubyte *)malloc(sizeof(GLubyte) * m_Width * m_Height * 4);
        memcpy(m_TextureData, imageData.data, sizeof(GLubyte)*m_Width*m_Height*4);

        FreeImage(imageData);
        
        return true;
    }
    
    void TextureMgr::Texture::Unload()
    {
        if(m_TextureData != nullptr)
        {
            free(m_TextureData);
            m_TextureData = nullptr;
        }
        m_Name.erase();
    }
}

