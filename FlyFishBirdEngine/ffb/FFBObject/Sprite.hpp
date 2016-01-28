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

namespace ffb {
    
    class Sprite: public Object {
        
    
        
    public:
        
        CreateClassFunctions(Sprite);
        
        bool Create(const std::string  &fileName);
        bool CreateLaunchImageForApple();
        
    private:
        
        
        Texture2D * m_texture;
        
        
        inline std::string CreateFileName(const std::string &fileName);
    };
}


#endif /* Sprite_hpp */
