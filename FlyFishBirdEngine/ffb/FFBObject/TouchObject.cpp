//
//  ClickObject.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/25.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TouchObject.hpp"


namespace ffb {
    
    
    void TouchObject::Clear()
    {
        Object::Clear();
        m_touchFunction = NULL;
        m_isTouched = false;
    }
    
    void TouchObject::Destory()
    {
        Object::Destory();
    }
    
    bool TouchObject::Create()
    {
        if (!Object::Create()) {
            return false;
        }
        
        return true;
    }
    
    
    void TouchObject::SetTouchFunction(TouchObjectFunction touchFunction)
    {
        m_touchFunction = touchFunction;
    }
    
    TouchObjectFunction TouchObject::GetTouchFunction()
    {
        return m_touchFunction;
    }
    
    
    
}