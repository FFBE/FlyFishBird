//
//  DrawObject.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "DrawObject.hpp"
#include "GameController.hpp"
#include <math.h>

namespace ffb {
    
    
    inline int round(const float a) {return int(a+0.5);}
    
    void DrawObject::Clear()
    {
        Object::Clear();
        m_pixNumber = 0;
    }
    
    bool DrawObject::Create()
    {
        if (!Object::Create()) {
            return false;
        }
                
        m_mesh->SetDrawType(FFBDrawTypePoints);
        m_mesh->SetVerticesStep(2);
        
        return true;
    }
    
    void DrawObject::Destory()
    {
        Object::Destory();
    }
    
    
    
#pragma mark - draw
    void DrawObject::DrawLine(int x0, int y0, int xEnd, int yEnd)
    {
        long size = GameController::GetSingletonPtr()->GetScreenWidth()*GameController::GetSingletonPtr()->GetScreenHeight();
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
        
        if (m_mesh->GetVertices() != nullptr) {
            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2-2));
            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber-1));
        }
        
        int dx = xEnd-x0, dy = yEnd-y0, steps, k;
        float xIncrement, yIncrement, x = x0, y= y0;
        
        if (std::abs(dx) > std::abs(dy)) {
            steps = std::abs(dx);
        }
        else{
            steps = std::abs(dy);
        }
        
        xIncrement = float(dx)/float(steps);
        yIncrement = float(dy)/float(steps);
        
        vertices[m_pixNumber*2] = round(x), vertices[m_pixNumber*2+1] = round(y);
        indices[m_pixNumber] = m_pixNumber;
        m_pixNumber ++;
        
        for (k = 0; k< steps; k++) {
            x += xIncrement;
            y += yIncrement;
            vertices[m_pixNumber*2] = round(x), vertices[m_pixNumber*2+1] = round(y);
            indices[m_pixNumber] = m_pixNumber;
            m_pixNumber ++;
        }
        
        m_mesh->SetVertices(vertices, m_pixNumber);
        m_mesh->SetIndices(indices, m_pixNumber);
        
        free(vertices), vertices = nullptr;
        free(indices), vertices = nullptr;
    }
    
    
    void DrawObject::DrawCircle(int xc, int yc, GLint radius)
    {
        long size = GameController::GetSingletonPtr()->GetScreenWidth()*GameController::GetSingletonPtr()->GetScreenHeight();
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
        
        if (m_mesh->GetVertices() != nullptr) {
            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2-2));
            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber-1));
        }
        
        GLfloat p = 4.0/5 - radius;
        GLint x = 0, y = radius;
        CirclePlotPoints(xc, yc, x, y, vertices, indices);
        
        while (x < y) {
            x++;
            if (p<0) {
                p += 2 * x + 1;
            }
            else{
                y--;
                p += 2* (x - y) + 1;
            }
            
            CirclePlotPoints(xc, yc, x, y, vertices, indices);
        }
        
        m_mesh->SetVertices(vertices, m_pixNumber);
        m_mesh->SetIndices(indices, m_pixNumber);
        
        free(vertices);
        free(indices);
    }
    
    void DrawObject::CirclePlotPoints(int xc, int yc, int x, int y, GLfloat *vertices, GLuint *indices)
    {
        for (int i = 0; i<8; i++) {
            switch (i) {
                case 0:
                    vertices[m_pixNumber*2] = xc+x, vertices[m_pixNumber*2+1] = yc+y;
                    break;
                    
                case 1:
                    vertices[m_pixNumber*2] = xc-x, vertices[m_pixNumber*2+1] = yc+y;
                    break;
                    
                case 2:
                    vertices[m_pixNumber*2] = xc+x, vertices[m_pixNumber*2+1] = yc-y;
                    break;
                    
                case 3:
                    vertices[m_pixNumber*2] = xc-x, vertices[m_pixNumber*2+1] = yc-y;
                    break;
                    
                case 4:
                    vertices[m_pixNumber*2] = xc+y, vertices[m_pixNumber*2+1] = yc+x;
                    break;
                    
                case 5:
                    vertices[m_pixNumber*2] = xc-y, vertices[m_pixNumber*2+1] = yc-x;
                    break;
                    
                case 6:
                    vertices[m_pixNumber*2] = xc-y, vertices[m_pixNumber*2+1] = yc+x;
                    break;
                    
                case 7:
                    vertices[m_pixNumber*2] = xc+y, vertices[m_pixNumber*2+1] = yc-x;
                    break;
                    
                default:
                    break;
            }
            indices[m_pixNumber] = m_pixNumber;
            m_pixNumber ++;
        }
    }
    
    void DrawObject::DrawCircleAndFill(int xc, int yc, GLint radius)
    {
        DrawLine(xc+radius, yc, xc-radius, yc);
        DrawLine(xc, yc+radius, xc, yc-radius);
        
        GLfloat p = 4.0/5 - radius;
        GLint x = 0, y = radius;
        
        while (x < y) {
            x++;
            if (p<0) {
                p += 2 * x + 1;
            }
            else{
                y--;
                p += 2* (x - y) + 1;
            }
            
            DrawLine(xc+x, yc+y, xc+x, yc-y);
            DrawLine(xc-x, yc+y, xc-x, yc-y);
            DrawLine(xc+y, yc+x, xc+y, yc-x);
            DrawLine(xc-y, yc+x, yc-y, yc-x);
        }
    }
    
}

