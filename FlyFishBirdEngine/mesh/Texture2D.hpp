//
//  FFBTexture2D.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp


#include <stdio.h>
#include "Mesh.hpp"

namespace ffb {
    class Texture2D: public Mesh {
        
        
    public:
        
        CreateClassFunctions(Texture2D);
        
        bool Create(std::string fileName);
        
        virtual void Render();
        
        float GetWidth();
        float GetHeight();
        
    private:
        
        float m_Width;
        float m_Height;
        
        GLuint m_textureId;
    };
}


#endif /* FFBTexture2D_hpp */
