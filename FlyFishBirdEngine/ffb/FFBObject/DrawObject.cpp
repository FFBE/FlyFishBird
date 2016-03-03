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
        m_mesh = FFBMalloc(Mesh);
        Object::Clear();
    }
    
    void DrawObject::Destory()
    {
        FFBSaveFree(m_mesh);
        Object::Destory();
    }

    
    bool DrawObject::Create()
    {
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
    
    void DrawObject::RemoveAllLine()
    {
        m_mesh->RemoveAllShap();
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
        m_mesh->AddShapData(indices, 2, vertices, 2, FFBDrawTypeLines, VerticesStepTwo,  Device::GetSingleton().GetScreenScale());
    }
    
    void DrawObject::DrawRectangle(Point leftDownPoint, Size size)
    {
        
    }
    
    void DrawObject::DrawCircle(int xc, int yc, GLint radius)
    {
        float scale = Device::GetSingleton().GetScreenScale();
        xc *= scale; yc *= scale; radius *= scale;
        
        long size = Device::GetSingletonPtr()->GetScreenWidth()*Device::GetSingletonPtr()->GetScreenHeight();
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
        int number = 0;
        
        GLfloat p = 4.0/5 - radius;
        GLint x = 0, y = radius;
        CirclePlotPoints(xc, yc, x, y, vertices, indices, number);
        while (x < y) {
            x++;
            if (p<0) {
                p += 2 * x + 1;
            }
            else{
                y--;
                p += 2* (x - y) + 1;
            }
            
            CirclePlotPoints(xc, yc, x, y, vertices, indices, number);
        }
        
        m_mesh->AddShapData(indices, number, vertices, number, FFBDrawTypePoints, VerticesStepTwo,  Device::GetSingleton().GetScreenScale());
        
        free(vertices);
        free(indices);
    }
    
    void DrawObject::CirclePlotPoints(int xc, int yc, int x, int y, GLfloat *vertices, GLuint *indices, int &startNumber)
    {
        for (int i = 0; i<8; i++) {
            switch (i) {
                case 0:
                    vertices[startNumber*2] = xc+x, vertices[startNumber*2+1] = yc+y;
                    break;
                    
                case 1:
                    vertices[startNumber*2] = xc-x, vertices[startNumber*2+1] = yc+y;
                    break;
                    
                case 2:
                    vertices[startNumber*2] = xc+x, vertices[startNumber*2+1] = yc-y;
                    break;
                    
                case 3:
                    vertices[startNumber*2] = xc-x, vertices[startNumber*2+1] = yc-y;
                    break;
                    
                case 4:
                    vertices[startNumber*2] = xc+y, vertices[startNumber*2+1] = yc+x;
                    break;
                    
                case 5:
                    vertices[startNumber*2] = xc-y, vertices[startNumber*2+1] = yc-x;
                    break;
                    
                case 6:
                    vertices[startNumber*2] = xc-y, vertices[startNumber*2+1] = yc+x;
                    break;
                    
                case 7:
                    vertices[startNumber*2] = xc+y, vertices[startNumber*2+1] = yc-x;
                    break;
                    
                default:
                    break;
            }
            indices[startNumber] = startNumber;
            startNumber ++;
        }
    }
    
    void DrawObject::DrawCircleAndFill(GLfloat xc, GLfloat yc, GLfloat radius)
    {
        float scale = Device::GetSingleton().GetScreenScale();
        
        xc *= scale; yc *= scale; radius *= scale;
        long size = Device::GetSingletonPtr()->GetScreenWidth()*Device::GetSingletonPtr()->GetScreenHeight();
        
        GLuint *indices = (GLuint *)malloc(sizeof(GLuint)*size);
        GLfloat *vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
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
            
            indices[number] = number;
            indices[number+1] = number+1;
            indices[number+2] = number+2;
            indices[number+3] = number+3;
            
            vertices[index] = xc+x;
            vertices[index+1] = yc+y;
            vertices[index+2] = xc+x;
            vertices[index+3] = yc-y;
            vertices[index+4] = xc-x;
            vertices[index+5] = yc-y;
            vertices[index+6] = xc-x;
            vertices[index+7] = yc+y;
            
            if (number>0 && vertices[index-8] == yc+y) {
                index -= 16;
                number += 4;
            }
            else
            {
                indices[number+4] = number+4;
                indices[number+5] = number+5;
                indices[number+6] = number+6;
                indices[number+7] = number+7;
                number += 8;
            }
            
            vertices[index+8] = yc+y;
            vertices[index+9] = xc+x;
            vertices[index+10] = yc+y;
            vertices[index+11] = xc-x;
            vertices[index+12] = yc-y;
            vertices[index+13] = xc-x;
            vertices[index+14] = yc-y;
            vertices[index+15] = xc+x;
        }
        
        indices[number] = number;
        indices[number+1] = number+1;
        
        vertices[number*2] = 0;
        vertices[number*2+1] = yc-radius;
        vertices[number*2+2] = 0;
        vertices[number*2+3] = yc+radius;
        
        m_mesh->AddShapData(indices, number+2, vertices, number+2, FFBDrawTypeLines, VerticesStepTwo, scale);
        
        free(indices);
        free(vertices);
    }
    
    
    //bezier
    
    void DrawObject::DrawBezier(Point point1, Point control1, Point control2, Point point2)
    {
        Point points[] = {point1, control1, control2, point2};
        DrawBezier(4, points,  round(Device::GetSingleton().GetScreenScale()));
    }
    
    void DrawObject::DrawBezier(Point point1, Point control, Point point2)
    {
        Point points[] = {point1, control, point2};
        DrawBezier(3, points,  round(Device::GetSingleton().GetScreenScale()));
    }
    
    void DrawObject::DrawBezier(int nCtrlPts, Point *ctrlPts, int width)
    {
        float scale = Device::GetSingleton().GetScreenScale();
        width = round(width);
        
        GLuint nBezCurvePts = 0;
        Point bezCurvePt, lastBezCurvePt;
        GLfloat u;
        GLint *C , i, j;
        GLint n = nCtrlPts-1;
        
        for (i = 0; i < nCtrlPts-1; i++) {
            nBezCurvePts += (fabsf(ctrlPts[i+1].x-ctrlPts[i].x) * scale);
            nBezCurvePts += (fabsf(ctrlPts[i+1].y-ctrlPts[i].y) * scale);
            
            ctrlPts[i].x *= scale;
            ctrlPts[i].y *= scale;
        }
        
        ctrlPts[i].x *= scale;
        ctrlPts[i].y *= scale;
        
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*nBezCurvePts*2*width);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*nBezCurvePts*width);
        int number = 0;
        nBezCurvePts *= 2;
        C = (GLint *)malloc(sizeof(GLint)*nBezCurvePts);
        
        for (i = 0 ; i <=  n; i++)
        {
            C[i] = 1;
            for (j= n; j >= i + 1; j--)
            {
                C[i] *= j;
            }
            for (j = n -i; j >= 2; j--)
            {
                C[i] /= j;
            }
        }
        
        for (i = 0; i <= nBezCurvePts; i++) {
            u = GLfloat(i)/GLfloat(nBezCurvePts);
            GLfloat bezBlendFcn;
            
            bezCurvePt.x = bezCurvePt.y = 0;
            
            for (j = 0; j < nCtrlPts; j++)
            {
                bezBlendFcn = C[j] * pow(u, j) * pow(1-u, n-j);
                bezCurvePt.x += ctrlPts [j].x * bezBlendFcn;
                bezCurvePt.y += ctrlPts [j].y * bezBlendFcn;
            }
            
            if (round(lastBezCurvePt.x) == round(bezCurvePt.x) && round(lastBezCurvePt.y) == round(bezCurvePt.y)) {
                continue;
            }
            
            float lowHeight = bezCurvePt.y - (width-1)/2;
            for (int i=0; i<width; i++)
            {
                vertices[number*2] = bezCurvePt.x;
                vertices[number*2+1] = lowHeight;
                indices[number] = number;
                number ++;
                lowHeight ++;
            }
            
            lastBezCurvePt = bezCurvePt;
        }
        
        m_mesh->AddShapData(indices, number, vertices, number, FFBDrawTypePoints, VerticesStepTwo, 1);
        
        free(vertices);
        free(indices);
        free(C);
    }
    
    
    void DrawObject::Draw(GLuint *indices, int numberOfIndeices, GLfloat *vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep)
    {
        m_mesh->AddShapData(indices, numberOfIndeices, vertices, numberOfVertices, type, verticesStep,  Device::GetSingleton().GetScreenScale());
    }
    
}

























