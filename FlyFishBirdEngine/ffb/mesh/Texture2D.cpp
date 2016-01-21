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

    }
    
    bool Texture2D::Create()
    {
        
        return true;
    }
    
    bool Texture2D::CreateImageTexture(std::string fileName)
    {
        if (!Renderer::Create()) {
            return false;
        }
        unsigned char * data;
        if (!GetImageInfo(fileName.c_str(), &data, &m_Height, &m_Width)) {
            printf("faild to create texture");
            return false;
        }
        SetTexture2d(data, m_Width, m_Height);
        free(data);
        return  true;
    }
    
    bool Texture2D::CreateStringTexture(std::string fontName, std::string text, float fontSize)
    {
        if (!Renderer::Create()) {
            return false;
        }
        unsigned char * data;
        if (!GetFontInfo(text.c_str(), fontName.c_str(), fontSize, &data, &m_Width, &m_Height))
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
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        
                
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        float scale = GameController::GetSingleton().GetScreenScale();
        
        m_Width /= scale;
        m_Height /= scale;
    }
    
    
    void Texture2D::Destory()
    {
        glDeleteTextures(1, &m_textureId);
        m_textureId = 0;
    }
    
    
    
    void Texture2D::Render()
    {
        MatrixLoadIdentity(&m_mvpMatrix);
        Translate(&m_mvpMatrix, m_point.x, m_point.y, 0);
        Scale(&m_mvpMatrix, m_scale.x, m_scale.y, 1);
        Rotate(&m_mvpMatrix, m_rotate, 0, 0, 1);
        Matrix camera = GameController::GetSingleton().GetCameraMatrix();
        MatrixMultiply(&m_mvpMatrix, &m_mvpMatrix, &camera);
        
        Size screenSize = GameController::GetSingletonPtr()->GetScreenSize();
        Point point = PointMake(m_point.x*2, m_point.y*2);
        GLfloat vVertices[] = {
            (-m_Width+point.x)/screenSize.width,  (m_Height+point.y)/screenSize.height, 0.0f,                      // Position 0
            0.0f,  0.0f,                                        // TexCoord 0
            (-m_Width+point.x)/screenSize.width, (-m_Height+point.y)/screenSize.height, 0.0f,                      // Position 1
            0.0f,  1.0f,                                        // TexCoord 1
            (m_Width+point.x)/screenSize.width, (-m_Height+point.y)/screenSize.height, 0.0f,                       // Position 2
            1.0f,  1.0f,                                        // TexCoord 2
            (m_Width+point.x)/screenSize.width,  (m_Height+point.y)/screenSize.height, 0.0f,                       // Position 3
            1.0f,  0.0f                                         // TexCoord 3
        };
        
        GLushort indices[] = { 0, 1, 2, 3 };

        glUseProgram ( m_glprogram->GetProgram() );
        m_glprogram->EnableTexture(1);
        
        MatrixLoadIdentity(&m_mvpMatrix);
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
    
    
    float Texture2D::GetHeight()
    {
        return m_Height;
    }
    
    
    float Texture2D::GetWidth()
    {
        return m_Width;
    }
    
    
    
    
    
    
}