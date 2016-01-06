//
//  Mesh.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/3.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Mesh.hpp"
#include "GameController.hpp"
#include "Define.h"

namespace ffb {
    
    void Mesh::Clear()
    {
        BasicPtrClass::Clear();
        
        m_rotate = 0;
        m_scale = PointMake(1, 1);
        m_point = PointMake(0, 0);
        
        m_shaderColor = ColorMake(0, 0, 0, 1);
        
        m_drawType = FFBDrawTypePoints;
        
        m_verticesStep = 3;
        m_numberOfIndeices = 0;
        m_numberOfVertices = 0;
        
        m_vertices = nullptr;
        m_indices = nullptr;
        
    }
    
    bool Mesh::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        Create(defaultProgram);

        return true;
    }
    
    bool Mesh::Create(short key)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        m_glprogram = GameController::GetSingleton().GetProgramWithKey(key);
        Create(m_glprogram);
        
        return true;
    }
    
    bool Mesh::Create(ffb::GLESProgram *programe)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_glprogram = programe;
        
        m_vboids[0] = 0; m_vboids[1] = 0;
        
        return true;
    }
    
    void Mesh::Destory()
    {
        FFBSaveFreeBaseType(m_vertices);
        FFBSaveFreeBaseType(m_indices);
        
        BasicPtrClass::Destory();
    }
    
    
#pragma mark - Render
    
    void Mesh::Render()
    {
        if (m_vertices == nullptr)
        {
            return;
        }
        // Use the program object
        glUseProgram ( m_glprogram->GetProgram() );
        
        MatrixLoadIdentity(&m_mvpMatrix);
        Translate(&m_mvpMatrix, m_point.x, m_point.y, 0);
        Scale(&m_mvpMatrix, m_scale.x, m_scale.y, 1);
        Rotate(&m_mvpMatrix, m_rotate, 0, 0, 1);
        Matrix camera = GameController::GetSingleton().GetCameraMatrix();
        MatrixMultiply(&m_mvpMatrix, &m_mvpMatrix, &camera);
        
        // Load the vertex data
        m_glprogram->SetMvpMatrix(m_mvpMatrix);
        
        glVertexAttrib4f(m_glprogram->GetColorIndex(), m_shaderColor.r, m_shaderColor.g, m_shaderColor.b, m_shaderColor.a);
        
        if (m_vboids[0] == 0 && m_vboids[1] == 0) {
            glGenBuffers(2, m_vboids);

            glBindBuffer(GL_ARRAY_BUFFER, m_vboids[0]);
            glBufferData(GL_ARRAY_BUFFER, m_verticesStep*sizeof(GLfloat)*m_numberOfVertices, m_vertices, GL_DYNAMIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_numberOfIndeices, m_indices, GL_DYNAMIC_DRAW);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vboids[0]);
        glEnableVertexAttribArray ( m_glprogram->GetPositionIndex() );
        glVertexAttribPointer ( m_glprogram->GetPositionIndex(), m_verticesStep, GL_FLOAT, GL_FALSE, m_verticesStep * sizeof ( GLfloat ), 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboids[1]);
        if (m_drawType == GL_TRIANGLE_FAN+1) {
            glDrawElements(GL_POINTS, m_numberOfIndeices, GL_UNSIGNED_INT, 0);
        }
        else
            glDrawElements(m_drawType, m_numberOfIndeices, GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(m_glprogram->GetPositionIndex());
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    }
    
#pragma mark - Transform
    
    void Mesh::SetPosition(Point point)
    {
        m_point = point;
    }
    
    void Mesh::SetPosition(float x, float y)
    {
        m_point.x = x;
        m_point.y = y;
    }
    
    Point Mesh::GetPosition()
    {
        return m_point;
    }
    
    void Mesh::SetScale(float scale)
    {
        m_scale.x = scale;
        m_scale.y = scale;
    }
    
    void Mesh::SetScale(float scaleX, float scaleY)
    {
        m_scale.x = scaleX;
        m_scale.y = scaleY;
    }
    
    void Mesh::SetScale(Point scale)
    {
        m_scale = scale;
    }
    
    Point Mesh::GetScale()
    {
        return m_scale;
    }
    
    void Mesh::SetRotate(float rotate)
    {
        m_rotate = rotate;
    }
    
    float Mesh::GetRotate()
    {
        return m_rotate;
    }
    
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
    
    void Mesh::SetDrawType(FFBDrawType type)
    {
        m_drawType = type;
    }
    
    void Mesh::SetIndices(GLuint *indices, int numberOfIndeices)
    {
        if (m_indices != nullptr) {
            free(m_indices);
        }
        m_numberOfIndeices = numberOfIndeices;
        m_indices = (GLuint *)malloc(sizeof(GLuint)*numberOfIndeices);
        memcpy(m_indices, indices, sizeof(GLuint)*numberOfIndeices);
        
//        std::cout<<m_numberOfIndeices<<std::endl;
        
    }
    
    void Mesh::SetVertices(GLfloat *vertices, int numberOfVertices)
    {
        if (m_vertices != nullptr) {
            free(m_vertices);
        }
        
        m_numberOfVertices = numberOfVertices;
        m_vertices = (GLfloat *)malloc(sizeof(GLfloat)*numberOfVertices*m_verticesStep);
        memcpy(m_vertices, vertices, sizeof(GLfloat)*numberOfVertices*m_verticesStep);
       
    }
    
    void Mesh::SetVerticesStep(unsigned int step)
    {
        m_verticesStep = step;
    }
    
    void Mesh::SetShapData(GLuint *indices, int numberOfIndeices, GLfloat *vertices, int numberOfVertices, FFBDrawType type)
    {
        SetIndices(indices, numberOfIndeices);
        SetVertices(vertices, numberOfVertices);
        SetDrawType(type);
    }
    
    
    
    FFBDrawType Mesh::GetDrawType()
    {
        return m_drawType;
    }
    
    unsigned int Mesh::GetVerticesStep()
    {
        return m_verticesStep;
    }
    
    int Mesh::GetNumberIndeices()
    {
        return m_numberOfIndeices;
    }
    
    GLuint * Mesh::GetIndices()
    {
        return m_indices;
    }
    
    GLfloat * Mesh::GetVertices()
    {
        return m_vertices;
    }
    
    
#pragma mark - mvp matrix
    
    Matrix Mesh::GetMvpMatrix()
    {
        return m_mvpMatrix;
    }
    
}



