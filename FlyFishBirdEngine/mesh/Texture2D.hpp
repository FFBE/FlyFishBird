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
        
        bool CreateImageTexture(std::string fileName);
        bool CreateStringTexture(std::string fontName, std::string text, float fontSize);
        
        void SetTexture2d(unsigned char * data, float width, float height);

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
