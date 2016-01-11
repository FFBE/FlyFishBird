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

namespace ffb {
    class DrawObject:public Object {
        
        
    public:
        
        CreateClassFunctions(DrawObject);
        
        Color GetColor();
                
        /* DDA line-drawing */
        void DrawLine(int x0, int y0, int xEnd, int yEnd);
        
        void DrawCircle(int xc, int yc, GLint radius);
        void DrawCircleAndFill(int xc, int yc, GLint radius);
        
        
    private:
        
        void CirclePlotPoints(int xc, int yc, int x, int y, GLfloat * vertices, GLuint * indices);

        
        int m_pixNumber;
    };
}


#endif /* FFBDrawObject_hpp */
