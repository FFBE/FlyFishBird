//
//  Texture2D.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include <string>
#include "GameController.hpp"

#include "Texture2D.hpp"
#include "Image.h"
#include "Font.h"


namespace ffb {
    
    void Texture2D::Clear()
    {
        m_textureId = 0;
        m_textureScale = PointMake(1, 1);
        m_textureWrap = TextureWrapModelClampToEdge;
        Renderer::Clear();
    }
    
    
    void Texture2D::Destory()
    {
        glDeleteTextures(1, &m_textureId);
        m_textureId = 0;
    }

    
    bool Texture2D::Create()
    {
        if (!Renderer::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool Texture2D::CreateImageTexture(const std::string &fileName)
    {
        if (!Renderer::Create()) {
            return false;
        }
        
        unsigned char * data;
        float textureHeight;
        float textureWidth;
        if (!GetImageInfo(fileName.c_str(), &data, &m_Width, &m_Height, &textureWidth, &textureHeight)) {
            printf("faild to create texture\n");
            return false;
        }
        SetTexture2d(data, textureWidth, textureHeight);
        free(data);
        return  true;
    }
    
    bool Texture2D::CreateStringTexture(const std::string &fontName, const std::string &text, float fontSize, Color color)
    {
        if (!Renderer::Create()) {
            return false;
        }
        unsigned char * data;
        if (!GetFontInfo(text.c_str(), fontName.c_str(), fontSize, &data, &m_Width, &m_Height, color.r, color.g, color.b, color.a))
        {
            printf("faild to create texture");
            return false;
        }
        SetTexture2d(data, m_Width, m_Height);
        free(data);
        return true;
    }
        
    void Texture2D::SetTexture2d(unsigned char *data, float width, float height)
    {
        if (m_textureId) {
            glDeleteTextures(1, &m_textureId);
        }
        
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        
        
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_textureWrap );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_textureWrap );
        
                
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        float scale = Device::GetSingleton().GetScreenScale();
        
        m_Width /= scale;
        m_Height /= scale;
    }
    
    
    void Texture2D::SetTextureScale(Point textureScale)
    {
        m_textureScale = textureScale;
    }
    
    void Texture2D::SetTextureScale(float x, float y)
    {
        m_textureScale = PointMake(x, y);
    }
    
    
    Point Texture2D::GetTextureScale()
    {
        return m_textureScale;
    }
    
    
    void Texture2D::SetTextureWrapModel(TextureWrapModel model)
    {
        m_textureWrap = model;
    }
    
    TextureWrapModel Texture2D::GetTextureWrapModel()
    {
        return m_textureWrap;
    }
    
    
    void Texture2D::Render()
    {
        float scale = Device::GetSingleton().GetScreenScale();
        
        Renderer::Render();
        
        GLfloat vVertices[] = {
            -m_Width*scale/2*m_textureScale.x,  m_Height*scale/2, 0.0f*m_textureScale.y,        // Position 0
            0.0f,  0.0f,                                                                        // TexCoord 0
            -m_Width*scale/2*m_textureScale.x, -m_Height*scale/2, 0.0f*m_textureScale.y,        // Position 1
            0.0f,  m_textureScale.y,                                                            // TexCoord 1
            m_Width*scale/2*m_textureScale.x, -m_Height*scale/2, 0.0f*m_textureScale.y,         // Position 2
            m_textureScale.x,  m_textureScale.y,                                                // TexCoord 2
            m_Width*scale/2*m_textureScale.x,  m_Height*scale/2, 0.0f*m_textureScale.y,         // Position 3
            m_textureScale.x,  0.0f                                                             // TexCoord 3
        };
        
        GLushort indices[] = { 0, 1, 2, 3 };
        
        glUseProgram ( m_glprogram->GetProgram() );
        m_glprogram->EnableTexture(1);
        
        m_glprogram->SetMvpMatrix(m_mvpMatrix);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Load the vertex position
        glVertexAttribPointer ( m_glprogram->GetPositionIndex(), 3, GL_FLOAT,
                               GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
        // Load the texture coordinate
        glVertexAttribPointer ( m_glprogram->GetTexcoord0Index(), 2, GL_FLOAT,
                               GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );
        
        glEnableVertexAttribArray ( m_glprogram->GetPositionIndex() );
        glEnableVertexAttribArray ( m_glprogram->GetTexcoord0Index() );
        
        // Bind the texture
        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture ( GL_TEXTURE_2D, m_textureId);
        
        // Set the sampler texture unit to 0
        
        glDrawElements ( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, indices );
        
        glDisableVertexAttribArray(m_glprogram->GetPositionIndex());
        glDisableVertexAttribArray(m_glprogram->GetTexcoord0Index());
        
        glDisable(GL_BLEND);
        m_glprogram->EnableTexture(0);
    }
    
    
    Size Texture2D::GetSize()
    {
        return SizeMake(m_Width, m_Height);
    }
    
    
    
    
    
    
}