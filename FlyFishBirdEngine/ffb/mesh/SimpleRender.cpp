//
//  SimpleRender.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/23.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "SimpleRender.hpp"

namespace ffb {
    
    void SimpleRender::Clear()
    {
        m_numberOfIndeices = 0;
        m_numberOfVertices = 0;
        m_indices = nullptr;
        m_vertices = nullptr;
        m_drawType = FFBDrawTypePoints;
        m_verticesStep = VerticesStepTwo;
        m_lineWidth = 1;
        m_color = ColorMake(1, 1, 1, 1);
        m_vboids[0] = 0, m_vboids[1] = 0;
        
        Renderer::Clear();
    }
    
    void SimpleRender::Destory()
    {
        FFBSaveFreeBaseType(m_vertices);
        FFBSaveFreeBaseType(m_indices);
        
        glDeleteBuffers(2, m_vboids);
        
        Renderer::Destory();
    }
    
    bool SimpleRender::Create()
    {
        if (!Renderer::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool SimpleRender::Create(int numberOfIndeices, int numberOfVertices, GLuint *indices, GLfloat *vertices, FFBDrawType drawType, VerticesStep verticesStep)
    {
        if (!Renderer::Create()) {
            return false;
        }
        
        FFBSaveFreeBaseType(m_indices);
        FFBSaveFreeBaseType(m_vertices);
        
        m_drawType = drawType;
        m_verticesStep = verticesStep;
        
        //set indices
        m_numberOfIndeices = numberOfIndeices;
        m_indices = (GLuint *)malloc(sizeof(GLuint) * numberOfIndeices);
        memcpy(m_indices, indices, sizeof(GLuint) * numberOfIndeices);
        
        
        //set vertices
        m_numberOfVertices = numberOfVertices;
        m_vertices = (GLfloat *)malloc(sizeof(GLfloat) * numberOfVertices * verticesStep);
        memcpy(m_vertices, vertices, sizeof(GLfloat) * numberOfVertices * verticesStep);
        
        return true;
    }
    
    void SimpleRender::SetIndices(int numberOfIndices, GLuint * indices)
    {
        FFBSaveFreeBaseType(m_indices);
        m_numberOfIndeices = numberOfIndices;
        m_indices = (GLuint *)malloc(sizeof(GLuint) * numberOfIndices);
        memcpy(m_indices, indices, sizeof(GLuint) * numberOfIndices);
    }
    
    void SimpleRender::SetVertices( int numberOfVertices, GLfloat * vertices, VerticesStep verticesStep)
    {
        FFBSaveFreeBaseType(m_vertices);
        m_verticesStep = verticesStep;
        m_numberOfVertices = numberOfVertices;
        m_vertices = (GLfloat *)malloc(sizeof(GLfloat) * numberOfVertices * verticesStep);
        memcpy(m_vertices, vertices, sizeof(GLfloat) * numberOfVertices * verticesStep);
    }
    
    void SimpleRender::SetDrawType( FFBDrawType drawType )
    {
        m_drawType = drawType;
    }
    
    void SimpleRender::SetLineWidth( float lineWidth )
    {
        m_lineWidth = lineWidth;
    }
    
    void SimpleRender::SetColor(float r, float g, float b, float a)
    {
        m_color = ColorMake(r, g, b, a);
    }
    
    void SimpleRender::SetColor(Color color)
    {
        m_color = color;
    }
    
    Color SimpleRender::GetColor()
    {
        return m_color;
    }
    
    void SimpleRender::Render()
    {
        Renderer::Render();
        
        glUseProgram ( m_glprogram->GetProgram() );
        
        m_glprogram->SetMvpMatrix(m_mvpMatrix);
        
        glVertexAttrib4f(m_glprogram->GetColorIndex(), m_color.r, m_color.g, m_color.b, m_color.a);
        
        
        // Load the vertex data
        if (m_vboids[0] == 0) {
            
            glGenBuffers(2, m_vboids);

            glBindBuffer(GL_ARRAY_BUFFER, m_vboids[0]);
            glBufferData(GL_ARRAY_BUFFER, m_verticesStep * sizeof(GLfloat) * m_numberOfVertices, m_vertices, GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_numberOfIndeices, m_indices, GL_STATIC_DRAW);
            
        }
        
        glLineWidth(m_lineWidth);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vboids[0]);
        glEnableVertexAttribArray ( m_glprogram->GetPositionIndex() );
        glVertexAttribPointer ( m_glprogram->GetPositionIndex(), m_verticesStep, GL_FLOAT, GL_FALSE, m_verticesStep * sizeof ( GLfloat ), 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[1]);
        if (m_drawType == FFBDrawTypePoints) {
            glDrawElements(GL_POINTS, m_numberOfIndeices, GL_UNSIGNED_INT, 0);
        }
        else
            glDrawElements(m_drawType, m_numberOfIndeices, GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(m_glprogram->GetPositionIndex());
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glLineWidth(1.0);
    }
    
}
