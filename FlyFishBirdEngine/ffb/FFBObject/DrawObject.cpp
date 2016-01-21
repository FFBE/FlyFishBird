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
        m_mesh = FFBMalloc(Mesh);
        if (!Object::Create(m_mesh)) {
            return false;
        }
        m_mesh->Create();
        m_mesh->SetDrawType(FFBDrawTypePoints);
        m_mesh->SetVerticesStep(2);
        
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
    
    void DrawObject::DrawLine(int x0, int y0, int xEnd, int yEnd)
    {
        float scale = GameController::GetSingleton().GetScreenScale();
        x0 *= scale; y0 *= scale; xEnd *= scale; yEnd *= scale;
        
        GLuint size = UINT32_MAX;
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size/2);
        
        if (m_mesh->GetVertices() != nullptr) {
            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2));
            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber));
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
        float scale = GameController::GetSingleton().GetScreenScale();
        xc *= scale; yc *= scale; radius *= scale;
        
        long size = GameController::GetSingletonPtr()->GetScreenWidth()*GameController::GetSingletonPtr()->GetScreenHeight();
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
        
        if (m_mesh->GetVertices() != nullptr) {
            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2));
            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber));
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
        float scale = GameController::GetSingleton().GetScreenScale();
        
        long size = GameController::GetSingletonPtr()->GetScreenWidth()*GameController::GetSingletonPtr()->GetScreenHeight();
        GLfloat * vertices = (GLfloat *)malloc(sizeof(GLfloat)*size*2);
        GLuint * indices = (GLuint *)malloc(sizeof(GLuint)*size);
        if (m_pixNumber > 0) {
            memcpy(vertices, m_mesh->GetVertices(), sizeof(GLfloat)*(m_pixNumber*2));
            memcpy(indices, m_mesh->GetIndices(), sizeof(GLuint)*(m_pixNumber));
        }
        
        GLuint nBezCurvePts = 0;
        Point bezCurvePt ;
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
            
            vertices[m_pixNumber*2] = bezCurvePt.x, vertices[m_pixNumber*2+1] = bezCurvePt.y, indices[m_pixNumber] = m_pixNumber;
            m_pixNumber ++;
        }
        
        m_mesh->SetVertices(vertices, m_pixNumber);
        m_mesh->SetIndices(indices, m_pixNumber);
        
        free(vertices);
        free(indices);
        free(C);
    }
    
    
    
    
    
    
    
}

























