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
#include "TextureMgr.hpp"

namespace ffb {
    class Texture2D: public Mesh {
        
    public:
    
        CreateClassFunctions(Texture2D);
        
        
        //texture for image
        
        bool CreateImageTexture(std::string fileName);
        
        
        // texture for text
    
        bool CreateStringTexture(std::string fontName, std::string text, float fontSize);
        void updateStirngTexture();
        void SetString(std::string text);
        
        
        
        void SetTexture2d(unsigned char * data, float width, float height);
        HTexture GetTextureHandle();
        
        virtual void Render();
        
        virtual float GetWidth();
        virtual float GetHeight();
        
    private:
        
        float m_Width;
        float m_Height;
        
        GLuint m_textureId;
        HTexture m_HTexture;
    };
}


#endif /* FFBTexture2D_hpp */
