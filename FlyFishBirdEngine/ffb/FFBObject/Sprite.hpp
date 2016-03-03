//
//  Sprite.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include "Object.hpp"
#include "Texture2D.hpp"

namespace ffb {
    
    class Sprite: public Object {
        
    
        
    public:
        
        CreateClassFunctions(Sprite);
        
        bool Create(const std::string  &fileName);
        bool Create(const std::string  &fileName, TextureWrapModel model);

        bool CreateLaunchImageForApple();
        
        std::string GetFileName();
        
        Size GetSize();
        
    protected:
        
        
        Texture2D * m_texture;
        
        std::string m_fileName;
//        inline std::string CreateFileName(const std::string &fileName);
    };
}


#endif /* Sprite_hpp */
