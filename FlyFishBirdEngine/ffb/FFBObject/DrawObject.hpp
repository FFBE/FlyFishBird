//
//  FFBDrawObject.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/8.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef DrawObject_hpp
#define DrawObject_hpp

#include <stdio.h>
#include "Object.hpp"
#include "Mesh.hpp"

namespace ffb {
    class DrawObject:public Object {
        
        
    public:
        
        CreateClassFunctions(DrawObject);
        
        Color GetColor();
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
    
        void DrawLine(int x0, int y0, int xEnd, int yEnd);
        
        
        void DrawCircle(int xc, int yc, GLint radius);
        void DrawCircleAndFill(int xc, int yc, GLint radius);
        
        
        void DrawBezier(int number, Point * points);
        void DrawBezier(Point point1, Point control1, Point control2, Point point2);
        void DrawBezier(Point point1, Point control, Point point2);
        
    private:
        
        void CirclePlotPoints(int xc, int yc, int x, int y, GLfloat * vertices, GLuint * indices);
        
        int m_pixNumber;
        
        Mesh * m_mesh;
    };
}


#endif /* FFBDrawObject_hpp */
