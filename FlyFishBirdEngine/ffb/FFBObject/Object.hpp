//
//  Object.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <vector>

#include "BasicPtrClass.hpp"

#include "Renderer.hpp"

#include "Texture2D.hpp"

namespace ffb {
    
    
    class Object:public BasicPtrClass{
        
    public:
        
        typedef std::vector<Object *> ObjectList;

        
        CreateClassFunctions(Object);
        
        bool Create(Renderer * render);
        
        void AddObject(Object *object);
        void RemoveObject(Object *object);
        void RemoveFromSuperObject();
        
        
        //position
        void SetPosition(Point point);
        void SetPosition(float x, float y);
        Point GetPosition();
        
        //scale
        void SetScale(float scale);
        void SetScale(Point scale);
        void SetScale(float x, float y);
        Point GetScale();
        
        //rotate
        void SetRotate(float angle);
        float GetRotate();
        
        
        
        void Render();
        virtual void update(double dt);
        
        
        //touch enable
        void SetTouchEnable(bool touchEnable);
        void GetTouchEnable();
        
        //touch event
        virtual bool TouchShouldBegin( Point touchPoint );
        virtual void TouchMoved(Point movePoint);
        virtual void TouchEnd(Point endPoint);
        
        //touch check
        Object * TouchCheck(Point touchPoint);
        

        
    protected:
        

        void SetRenderer(Renderer *);
        
        Point           m_scale;
        Point           m_position;
        float           m_rotate;
        
        Object        * m_supObject;
        ObjectList      m_objectList;
        Renderer      * m_render;
        
    private:
        
        bool            m_touchEnable;
        
        

    };
    
    
}




#endif /* Object_hpp */
