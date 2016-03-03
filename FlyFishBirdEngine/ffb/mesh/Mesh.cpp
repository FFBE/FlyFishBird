//
//  Mesh.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/3.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Mesh.hpp"
#include "GameController.hpp"
#include "Macro.h"

namespace ffb {
    
    void Mesh::Clear()
    {
        Renderer::Clear();

        m_shaderColor = ColorMake(0, 0, 0, 1);
        
        m_vboids = nullptr;
        
    }
    
    void Mesh::Destory()
    {
        RemoveAllShap();
        Renderer::Destory();
    }
    
    bool Mesh::Create()
    {
        if (!Renderer::Create()) {
            return false;
        }
        
        m_meshVector.reserve(10);
        
        return true;
    }
    
    void Mesh::RemoveAllShap()
    {
        for (MeshAttribute mesh : m_meshVector) {
            FFBSaveFreeBaseType(mesh.vertices);
            FFBSaveFreeBaseType(mesh.indices);
        }
        
        glDeleteBuffers((GLsizei)m_meshVector.size(), m_vboids);
        FFBSaveFreeBaseType(m_vboids);
        m_meshVector.clear();
    }
    
#pragma mark - Render
    
    void Mesh::Render()
    {
        if (m_meshVector.empty())
        {
            return;
        }
                
        Renderer::Render();
        
        // Use the program object
        glUseProgram ( m_glprogram->GetProgram() );
        
        m_glprogram->SetMvpMatrix(m_mvpMatrix);
        
        glVertexAttrib4f(m_glprogram->GetColorIndex(), m_shaderColor.r, m_shaderColor.g, m_shaderColor.b, m_shaderColor.a);
        
        
        // Load the vertex data
        if (m_vboids == nullptr) {
            
            int i = 0, number = (int)m_meshVector.size()*2;
            m_vboids = (GLuint *)malloc(sizeof(GLuint) * number);
            glGenBuffers(number, m_vboids);
            
            MeshAttributeVector::iterator itera = m_meshVector.begin(), end = m_meshVector.end();
            for (; itera != end; ++itera, ++i) {
                MeshAttribute meshAttribute = *itera;
                
                glBindBuffer(GL_ARRAY_BUFFER, m_vboids[2*i]);
                glBufferData(GL_ARRAY_BUFFER, meshAttribute.verticesStep*sizeof(GLfloat)*meshAttribute.numberOfVertices, meshAttribute.vertices, GL_STATIC_DRAW);
                
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[2*i+1]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*meshAttribute.numberOfIndeices, meshAttribute.indices, GL_STATIC_DRAW);
            }
        }
        
        int i = 0;
        MeshAttributeVector::iterator itera = m_meshVector.begin(), end = m_meshVector.end();
        for (; itera != end; ++itera, ++i) {
            MeshAttribute meshAttribute = *itera;
            
            glLineWidth(meshAttribute.lineWidth);
            
            glBindBuffer(GL_ARRAY_BUFFER, m_vboids[2*i]);
            glEnableVertexAttribArray ( m_glprogram->GetPositionIndex() );
            glVertexAttribPointer ( m_glprogram->GetPositionIndex(), meshAttribute.verticesStep, GL_FLOAT, GL_FALSE, meshAttribute.verticesStep * sizeof ( GLfloat ), 0);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[2*i+1]);
            if (meshAttribute.drawType == FFBDrawTypePoints) {
                glDrawElements(GL_POINTS, meshAttribute.numberOfIndeices, GL_UNSIGNED_INT, 0);
            }
            else
                glDrawElements(meshAttribute.drawType, meshAttribute.numberOfIndeices, GL_UNSIGNED_INT, 0);
            
            glDisableVertexAttribArray(m_glprogram->GetPositionIndex());
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        glLineWidth(1.0);
    }
    
#pragma mark - Transform
    
    void Mesh::SetColor(float r, float g, float b, float a)
    {
        m_shaderColor.r = r;
        m_shaderColor.g = g;
        m_shaderColor.b = b;
        m_shaderColor.a = a;
    }
    
    void Mesh::SetColor(Color color)
    {
        m_shaderColor = color;
    }
    
    Color Mesh::GetColor()
    {
        return m_shaderColor;
    }
    
    
#pragma mark - Shap data
    
    
    void Mesh::AddShapData(GLuint *indices, int numberOfIndeices, GLfloat *vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep, GLfloat lineWidth)
    {
        if (m_vboids != nullptr) {
            glDeleteBuffers((GLsizei)m_meshVector.size(), m_vboids);
            m_vboids = nullptr;
        }
        
        MeshAttribute meshAttribute;
        
        meshAttribute.lineWidth = lineWidth;
        meshAttribute.verticesStep = verticesStep;
        meshAttribute.drawType = type;
        
        //set indices
        meshAttribute.numberOfIndeices = numberOfIndeices;
        meshAttribute.indices = (GLuint *)malloc(sizeof(GLuint) * numberOfIndeices);
        memcpy(meshAttribute.indices, indices, sizeof(GLuint) * numberOfIndeices);
        
        
        //set vertices
        meshAttribute.numberOfVertices = numberOfVertices;
        meshAttribute.vertices = (GLfloat *)malloc(sizeof(GLfloat) * numberOfVertices * verticesStep);
        memcpy(meshAttribute.vertices, vertices, sizeof(GLfloat) * numberOfVertices * verticesStep);
        
        m_meshVector.push_back(meshAttribute);
    }
    
}



