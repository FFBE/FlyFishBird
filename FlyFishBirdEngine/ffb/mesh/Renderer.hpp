//
//  Renderer.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/15.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "SimpleMath.h"
#include "GLESProgram.hpp"

#include "BasicPtrClass.hpp"

namespace ffb {
    class Renderer:public BasicPtrClass  {
        
        
    public:
        
        CreateClassFunctions(Renderer);
        bool Create(short key);
        bool Create(GLESProgram * programe);
        
        /*position*/
        void SetPosition(Point point);
        void SetPosition(float x, float y);
        Point  GetPosition();
        
        void SetSize(Size size);
        void SetSize(float width, float height);
        Size  GetSize();
        
        void SetScale(float scale);
        void SetScale(float scaleX, float scaleY);
        void SetScale(Point scale);
        Point GetScale();
        
        void SetRotate(float rotate);
        float GetRotate();
        
        //render
        
        virtual void Render();
        
    protected:
        
        Point            m_point;
        
        //scale default 1
        Point            m_scale;
        
        //360r   default 0    clock wise
        float            m_rotate;
        
        
        GLESProgram      *m_glprogram;
        
        Matrix           m_mvpMatrix;
        
        
    };
}



#endif /* Renderer_hpp */
