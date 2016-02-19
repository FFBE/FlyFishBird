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
#include "Renderer.hpp"

namespace ffb {
    class Texture2D: public Renderer {
        
    public:
    
        CreateClassFunctions(Texture2D);
        
        
        //texture for image
        
        bool CreateImageTexture(const std::string &fileName);
        
        
        // texture for text
    
        bool CreateStringTexture(const std::string &fontName,const std::string &text, float fontSize);
        void updateStirngTexture();
        void SetString(const std::string &text);
        void SetStringColor(float r, float g, float b, float a);
        
        void SetTexture2d(unsigned char * data, float width, float height);
        
        virtual void Render();
        
        virtual float GetWidth();
        virtual float GetHeight();
        
    private:
        
        float m_Width;
        float m_Height;
        
        GLuint m_textureId;
    };
}


#endif /* FFBTexture2D_hpp */
