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

#include "SimpleFunction.h"

#include "BasicPtrClass.hpp"
#include "Renderer.hpp"
#include "Action.hpp"

namespace ffb {
    
    class Touch:public BasicPtrClass
    {
        
    public:
        
        CreateClassFunctions(Touch);
        bool Create(Point point, double timestamp);
        
        Point GetTouchPoint() {return m_point;}
        double GetTouchTimestamp() {return m_touchTimestamp;}
        Point ConverTouchPointToObject(Object * object);
        
    private:
        
        Point m_point;
        double m_touchTimestamp;
        
    };
    
    
#define TouchEventFuncation\
    virtual bool TouchShouldBegin( ffb::Touch * touch );\
    virtual void TouchMoved(ffb::Touch * touch);\
    virtual void TouchEnd(ffb::Touch * touch)
    
    class Object:public BasicPtrClass{
        
        friend Touch;
        
    public:
        
        typedef std::vector<Object *> ObjectList;

        
        CreateClassFunctions(Object);
        
        bool Create(Renderer * render);
        
        
        //object
        void AddObject(Object *object);
        void RemoveObject(Object *object);
        void RemoveAllObject();
        void RemoveFromSuperObject();
        
        void SetTag(int tag);
        int GetTag();
        
        //hidden
        
        void SetHidden(bool hidden);
        bool GetHidden();
        
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
        
        
        //action
        void AddAction(Action * action);
        void RemoveAction(Action * action);
        void RemoveActionByTag(int tag);
        
        //render
        virtual void Render();
        virtual void Update(double dt);
        
        
        //touch enable
        void SetTouchEnable(bool touchEnable);
        bool GetTouchEnable();
        
        //touch event
        TouchEventFuncation;
        
        //touch check
        virtual Object * TouchCheck(Touch * touch);
        
        
        Renderer * GetRenderer();
        
    protected:
        

        void SetRenderer(Renderer *);
        
        Point           m_scale;
        Point           m_position;
        float           m_rotate;
        
        Object        * m_supObject;
        ObjectList      m_objectList;
        Renderer      * m_renderer;
        
        bool            m_touchEnable;
        bool            m_hidden;
        int             m_tag;
        
    private:
        
        
        

    };
    
}




#endif /* Object_hpp */
