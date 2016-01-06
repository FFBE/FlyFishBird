//
//  FFBTextureManager.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/11.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "FFBTextureManager.hpp"
#include <iostream>

namespace ffb {
    
    void FFBTextureManager::AddTexture(ffb::FFBTexture2D *texture, std::string key)
    {
        FFBTexture2D * searchTexture = nullptr;
        Texture2DMap::iterator itera;
        
        if (!m_texture2D.empty()) {
            itera = m_texture2D.find(key);
            if (itera != m_texture2D.end()) {
                searchTexture = (FFBTexture2D *)(*itera).second;
            }
        }
        
        if (searchTexture != nullptr) {
            return;
        }
        
        texture->retain();
        m_texture2D.insert(InsertTextureMapType(key, texture));
    }

    FFBTexture2D * FFBTextureManager::GetTexture(std::string key)
    {
        if (m_texture2D.empty()) {
            return nullptr;
        }
        
        Texture2DMap::iterator itera;
        itera = m_texture2D.find(key);
        if (itera == m_texture2D.end()) {
            return nullptr;
        }
        
        return (FFBTexture2D *)(*itera).second;
    }
    
    
    void FFBTextureManager::RemoveTexture(std::string key)
    {
        if (m_texture2D.empty()) {
            printf("have no texture");
            return;
        }
        
        Texture2DMap::iterator itera;
        itera = m_texture2D.find(key);
        if (itera == m_texture2D.end()) {
            FFBTexture2D * texture = (FFBTexture2D *)(*itera).second;
            texture->release();
            
            m_texture2D.erase(itera);
        }
        else {
            std::cout<<"texture "<<key<<" not find"<<std::endl;
        }
       
    }
    
}


