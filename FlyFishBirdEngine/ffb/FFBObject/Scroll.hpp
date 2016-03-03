//
//  Scroll.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/25.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Scroll_hpp
#define Scroll_hpp

#include <stdio.h>
#include "TouchObject.hpp"

namespace ffb {
    
    //can only move up and down
    class Scroll : public Object{
      
    public:
        
        CreateClassFunctions(Scroll);
        
        bool Create(Size size, Size contentOfSize);
        
        void AddObjectToScroll(TouchObject * object);
        void AddObjectsToScroll(std::vector<TouchObject *> objectList);
        
        void SetCutOffIfOut(bool cutOffIfOut);
        bool GetCutOffIfOut();
        
        virtual void Update(double dt);
        virtual void Render();
        
        Point GetScrollOfSet();
        void SetScrollOfSet(Point scrollOfSet);
        void SetScrollOfSet(Point scrollOfSet, bool animation);
        void SetScrollOfSet(Point scrollOfSet, bool animation, float time);

        void SetContentSize(Size contentSize);
        Size GetContentSize();
        
        void SetSize(Size size);
        Size GetSize();
        
        // if begin from top, origin in the lefttop.  default is true
        void SetBeginFromTop(bool beginFormTop);
        bool GetBeginFromTop();
        
        TouchEventFuncation;

    private:
        
        void SubObjectCannotTouch();
                
        bool m_cutOffIfOut;
        
        Size m_size;
        
        Point m_scrollOffSet;
        Size m_contentSize;
        
        bool m_beginFromTop;
        
        bool m_subObjectCanTouch;
        
        Point m_lastMovePoint;
        double m_lastTouchTime;
        
        float m_scrollSpeed;
        float m_scrollDeceleration;
        
        bool m_canScroll;
    };
    
}


#endif /* Scroll_hpp */
