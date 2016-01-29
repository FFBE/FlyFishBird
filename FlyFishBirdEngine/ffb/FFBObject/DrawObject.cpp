//
//  DrawObject.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "DrawObject.hpp"
#include "Device.hpp"
#include <math.h>

namespace ffb {
    
    
    inline int round(const float a) {return int(a+0.5);}
    
    void DrawObject::Clear()
    {
        Object::Clear();
    }
    
    bool DrawObject::Create()
    {
        m_mesh = FFBMalloc(Mesh);
        if (!Object::Create(m_mesh)) {
            return false;
        }
        if (!m_mesh->Create())
        {
            m_mesh->release();
            return false;
        }
        
        return true;
    }
    
    void DrawObject::Destory()
    {
        FFBSaveFree(m_mesh);
        Object::Destory();
    }
    
    
    
    void DrawObject::SetColor(float r, float g, float b, float a)
    {
        m_mesh->SetColor(r, g, b, a);
    }
    
    void DrawObject::SetColor(Color color)
    {
        m_mesh->SetColor(color);
    }
    
    Color DrawObject::GetColor()
    {
        return m_mesh->GetColor();
    }
    
    
#pragma mark - draw
    
    void DrawObject::DrawLine(GLfloat x0, GLfloat y0, GLfloat xEnd, GLfloat yEnd)
    {
        float scale = Device::GetSingleton().GetScreenScale();
        x0 *= scale; y0 *= scale; xEnd *= scale; yEnd *= scale;
        GLuint indices[2] = {0, 1};
        GLfloat vertices[4] = {x0, y0, xEnd, yEnd};
        m_mesh->AddShapData(indices, 2, vertices, 2, FFBDrawTypeLines, VerticesStepTwo);
    }
    
    void DrawObject::DrawCircle(int xc, int yc, GLint radius)
    {
//        float scale = Device::GetSingleton().GetScreenScale();
//        xc *= scale; yc *= scale; radius *= scale;
//        
//        long size = Device::GetSingletonPtr()->GetScreenWidth()*Device::GetSingletonPtr()->GetScreenHeight();
//        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
//        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
//        
//        if (m_mesh->GetVertices() != nullptr) {
//            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2));
//            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber));
//        }
//        
//        GLfloat p = 4.0/5 - radius;
//        GLint x = 0, y = radius;
//        CirclePlotPoints(xc, yc, x, y, vertices, indices);
//        
//        while (x < y) {
//            x++;
//            if (p<0) {
//                p += 2 * x + 1;
//            }
//            else{
//                y--;
//                p += 2* (x - y) + 1;
//            }
//            
//            CirclePlotPoints(xc, yc, x, y, vertices, indices);
//        }
//        
//        m_mesh->SetVertices(vertices, m_pixNumber);
//        m_mesh->SetIndices(indices, m_pixNumber);
//        
//        free(vertices);
//        free(indices);
    }
    
    void DrawObject::CirclePlotPoints(int xc, int yc, int x, int y, GLfloat *vertices, GLuint *indices)
    {
//        for (int i = 0; i<8; i++) {
//            switch (i) {
//                case 0:
//                    vertices[m_pixNumber*2] = xc+x, vertices[m_pixNumber*2+1] = yc+y;
//                    break;
//                    
//                case 1:
//                    vertices[m_pixNumber*2] = xc-x, vertices[m_pixNumber*2+1] = yc+y;
//                    break;
//                    
//                case 2:
//                    vertices[m_pixNumber*2] = xc+x, vertices[m_pixNumber*2+1] = yc-y;
//                    break;
//                    
//                case 3:
//                    vertices[m_pixNumber*2] = xc-x, vertices[m_pixNumber*2+1] = yc-y;
//                    break;
//                    
//                case 4:
//                    vertices[m_pixNumber*2] = xc+y, vertices[m_pixNumber*2+1] = yc+x;
//                    break;
//                    
//                case 5:
//                    vertices[m_pixNumber*2] = xc-y, vertices[m_pixNumber*2+1] = yc-x;
//                    break;
//                    
//                case 6:
//                    vertices[m_pixNumber*2] = xc-y, vertices[m_pixNumber*2+1] = yc+x;
//                    break;
//                    
//                case 7:
//                    vertices[m_pixNumber*2] = xc+y, vertices[m_pixNumber*2+1] = yc-x;
//                    break;
//                    
//                default:
//                    break;
//            }
//            indices[m_pixNumber] = m_pixNumber;
//            m_pixNumber ++;
//        }
    }
    
    void DrawObject::DrawCircleAndFill(GLfloat xc, GLfloat yc, GLfloat radius)
    {
        float scale = Device::GetSingleton().GetScreenScale();
        xc *= scale, yc *= scale, radius*=scale;
        
        GLuint *indices = (GLuint *)malloc(sizeof(GLuint)*10000);
        GLfloat *vertices = (GLfloat *)malloc(sizeof(GLfloat)*20000);
        GLuint number = 0;
        
        GLfloat p = 4.0/5 - radius;
        GLfloat x = 0, y = radius;
        
        while (x < y) {
            x++;
            if (p<0) {
                p += 2 * x + 1;
            }
            else{
                y--;
                p += 2* (x - y) + 1;
            }
            
            int index = 2*number;
            
            indices[index] = number;
            indices[index+1] = number+1;
            indices[index+2] = number+1;
            indices[index+3] = number+2;
            indices[index+4] = number+2;
            indices[index+5] = number+3;
            indices[index+6] = number+3;
            indices[index+7] = number;
            
            indices[index+8] = number+4;
            indices[index+9] = number+5;
            indices[index+10] = number+5;
            indices[index+11] = number+6;
            indices[index+12] = number+6;
            indices[index+13] = number+7;
            indices[index+14] = number+7;
            indices[index+15] = number+4;

            vertices[index] = xc+x;
            vertices[index+1] = yc+y;
            vertices[index+2] = xc+x;
            vertices[index+3] = yc-y;
            vertices[index+4] = xc-x;
            vertices[index+5] = yc-y;
            vertices[index+6] = xc-x;
            vertices[index+7] = yc+y;
            
            vertices[index+8] = yc+y;
            vertices[index+9] = xc+x;
            vertices[index+10] = yc-y;
            vertices[index+11] = xc+x;
            vertices[index+12] = yc-y;
            vertices[index+13] = xc-x;
            vertices[index+14] = yc+y;
            vertices[index+15] = xc-x;
            
            number += 8;
        }
        
        indices[number*2] = number;
        indices[number*2+1] = number+1;
        
        vertices[number*2] = 0;
        vertices[number*2+1] = yc-radius;
        vertices[number*2] = 0;
        vertices[number*2+1] = yc+radius;
        
        m_mesh->AddShapData(indices, 2*number+2, vertices, number+2, FFBDrawTypeLines, VerticesStepTwo);
    }
    
    
    //bezier
    
    void DrawObject::DrawBezier(Point point1, Point control1, Point control2, Point point2)
    {
        Point points[] = {point1, control1, control2, point2};
        DrawBezier(4, points);
    }
    
    void DrawObject::DrawBezier(Point point1, Point control, Point point2)
    {
        Point points[] = {point1, control, point2};
        DrawBezier(3, points);
    }
    
    void DrawObject::DrawBezier(int nCtrlPts, Point *ctrlPts)
    {
//        float scale = Device::GetSingleton().GetScreenScale();
//        
//        long size = Device::GetSingletonPtr()->GetScreenWidth()*Device::GetSingletonPtr()->GetScreenHeight();
//        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
//        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
//        if (m_pixNumber > 0) {
//            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2));
//            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber));
//        }
//        
//        GLuint nBezCurvePts = 0;
//        Point bezCurvePt ;
//        GLfloat u;
//        GLint *C , i, j;
//        GLint n = nCtrlPts-1;
//
//        for (i = 0; i < nCtrlPts-1; i++) {
//            nBezCurvePts += (fabsf(ctrlPts[i+1].x-ctrlPts[i].x) * scale);
//            nBezCurvePts += (fabsf(ctrlPts[i+1].y-ctrlPts[i].y) * scale);
//            
//            ctrlPts[i].x *= scale;
//            ctrlPts[i].y *= scale;
//        }
//        
//        ctrlPts[i].x *= scale;
//        ctrlPts[i].y *= scale;
//        
//        C = (GLint *)malloc(sizeof(GLint)*nBezCurvePts);
//        
//        for (i = 0 ; i <=  n; i++)
//        {
//            C[i] = 1;
//            for (j= n; j >= i + 1; j--)
//            {
//                C[i] *= j;
//            }
//            for (j = n -i; j >= 2; j--)
//            {
//                C[i] /= j;
//            }
//        }
//        
//        for (i = 0; i <= nBezCurvePts; i++) {
//            u = GLfloat(i)/GLfloat(nBezCurvePts);
//            GLfloat bezBlendFcn;
//            
//            bezCurvePt.x = bezCurvePt.y = 0;
//            
//            for (j = 0; j < nCtrlPts; j++)
//            {
//                bezBlendFcn = C[j] * pow(u, j) * pow(1-u, n-j);
//                bezCurvePt.x += ctrlPts [j].x * bezBlendFcn;
//                bezCurvePt.y += ctrlPts [j].y * bezBlendFcn;
//            }
//            
//            vertices[m_pixNumber*2] = bezCurvePt.x, vertices[m_pixNumber*2+1] = bezCurvePt.y, indices[m_pixNumber] = m_pixNumber;
//            m_pixNumber ++;
//        }
//        
//        m_mesh->SetVertices(vertices, m_pixNumber);
//        m_mesh->SetIndices(indices, m_pixNumber);
//        
//        free(vertices);
//        free(indices);
//        free(C);
    }
    
    
    void DrawObject::Draw(GLuint *indices, int numberOfIndeices, GLfloat *vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep)
    {
        m_mesh->AddShapData(indices, numberOfIndeices, vertices, numberOfVertices, type, verticesStep);
    }
    
}

























