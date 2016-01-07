//
//  Texture2D.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Texture2D.hpp"
#include "GameController.hpp"
#include "TextureMgr.hpp"
#include "FontMgr.hpp"

#include <string>
#include "GameController.hpp"


namespace ffb {
    
    void Texture2D::Clear()
    {
        m_textureId = 0;

        Mesh::Clear();
    }
    
    bool Texture2D::Create()
    {
        if (!Mesh::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool Texture2D::CreateTexture(unsigned char *data, float width, float height)
    {
        if (!Mesh::Create()) {
            return false;
        }
        
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        return true;
    }
    
    bool Texture2D::CreateImageTexture(std::string fileName)
    {
        HTexture m_HTexture = TextureMgr::GetSingletonPtr()->GetTexture(fileName.c_str());
        m_Width = TextureMgr::GetSingletonPtr()->GetWidth(m_HTexture);
        m_Height = TextureMgr::GetSingletonPtr()->GetHeight(m_HTexture);
        
        float scale = GameController::GetSingleton().GetScreenScale();
        
        m_Width /= scale;
        m_Height /= scale;
        
        return CreateTexture(TextureMgr::GetSingletonPtr()->GetTextureData(m_HTexture), m_Width*scale, m_Height*scale);
    }
    
    bool Texture2D::CreateStringTexture(std::string fontName, std::string text, float fontSize)
    {
        HFont hfont = FontMgr::GetSingletonPtr()->GetFont(fontName, text, fontSize);
        m_Width = FontMgr::GetSingletonPtr()->GetWidth(hfont);
        m_Height = FontMgr::GetSingletonPtr()->GetHeight(hfont);
        
        float scale = GameController::GetSingleton().GetScreenScale();
        
        m_Width /= scale;
        m_Height /= scale;
        
        return CreateTexture(FontMgr::GetSingletonPtr()->GetFontData(hfont), m_Width*scale, m_Height*scale);
    }
    
    void Texture2D::Destory()
    {
        glDeleteTextures(1, &m_textureId);

        Mesh::Destory();
    }
    
    void Texture2D::Render()
    {
       
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
        
        GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

        glUseProgram ( m_glprogram->GetProgram() );
        m_glprogram->EnableTexture(1);
        MatrixLoadIdentity(&m_mvpMatrix);
        m_glprogram->SetMvpMatrix(m_mvpMatrix);

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
        
        glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
        
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