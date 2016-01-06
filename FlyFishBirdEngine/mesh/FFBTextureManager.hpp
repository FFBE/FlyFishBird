//
//  FFBTextureManager.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/11.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef FFBTextureManager_hpp
#define FFBTextureManager_hpp

#include <stdio.h>
#include "CommonTeplate.hpp"
#include <map>
#include "FFBTexture2D.hpp"

namespace ffb {
    
    typedef std::map<std::string, FFBTexture2D *> Texture2DMap;
    
#define InsertTextureMapType(key, value)  std::map<std::string, FFBTexture2D *>::value_type(key, value)
    
    class FFBTextureManager:Singleton<FFBTextureManager> {
        
        
    public:
        
        
        FFBTexture2D * GetTexture(std::string key);
        void AddTexture(FFBTexture2D * texture, std::string key);
        void RemoveTexture(std::string key);
        
        
    private:
        
        Texture2DMap m_texture2D;
        
    };
}


#endif /* FFBTextureManager_hpp */
