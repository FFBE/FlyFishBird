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
        
        void DrawLine(GLfloat x0, GLfloat y0, GLfloat xEnd, GLfloat yEnd);
        
        
        void DrawCircle(int xc, int yc, GLint radius);
        void DrawCircleAndFill(GLfloat xc, GLfloat yc, GLfloat radius);
        
        
        void DrawBezier(int number, Point * points, int width);
        void DrawBezier(Point point1, Point control1, Point control2, Point point2);
        void DrawBezier(Point point1, Point control, Point point2);
        
        
        void Draw(GLuint * indices, int numberOfIndeices, GLfloat * vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep);
        
    private:
        
        void CirclePlotPoints(int xc, int yc, int x, int y, GLfloat * vertices, GLuint * indices, int &startNumber);
        
        Mesh * m_mesh;
    };
}


#endif /* FFBDrawObject_hpp */
