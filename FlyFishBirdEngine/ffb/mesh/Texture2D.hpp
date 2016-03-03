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
#include "SimpleRender.hpp"

namespace ffb {
    
    typedef enum {
        
        TextureWrapModelRepeat              =   GL_REPEAT,
        TextureWrapModelClampToEdge         =   GL_CLAMP_TO_EDGE,
        TextureWrapModelMirroredRepeat     =   GL_MIRRORED_REPEAT
        
    }TextureWrapModel;
    
    class Texture2D: public SimpleRender {
        
    public:
    
        CreateClassFunctions(Texture2D);
        
        
        //texture for image
        
        bool CreateImageTexture(const std::string &fileName);
        
        
        // texture for text
    
        bool CreateStringTexture(const std::string &fontName,const std::string &text, float fontSize, Color color);
        void updateStirngTexture();
        
        void SetTexture2d(unsigned char * data, float width, float height);
        
        virtual void Render();
        
        void SetTextureScale(Point textureScale);
        void SetTextureScale(float x, float y);
        Point GetTextureScale();
        
        Size GetSize();
        
        void SetTextureWrapModel(TextureWrapModel model);
        TextureWrapModel GetTextureWrapModel();
        
    private:
        
        float m_Width;
        float m_Height;
        
        float m_textureWidth;
        float m_textureHeight;
        
        GLuint m_textureId;
        
        Point m_textureScale;
        
        TextureWrapModel m_textureWrap;
    };
}


#endif /* FFBTexture2D_hpp */
