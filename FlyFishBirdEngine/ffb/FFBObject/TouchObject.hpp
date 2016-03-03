//
//  ClickObject.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/25.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef ClickObject_hpp
#define ClickObject_hpp

#include <stdio.h>
#include "Object.hpp"

namespace ffb {
    
    class TouchObject;
    
    typedef std::function< void (TouchObject *)> TouchObjectFunction;

    class TouchObject: public Object{
      
        
    public:
        
        CreateClassFunctions(TouchObject);
        
        void SetTouchFunction(TouchObjectFunction touchFunction);
        TouchObjectFunction GetTouchFunction();
        
        
    protected:
        
        bool                        m_isTouched;
        
        TouchObjectFunction         m_touchFunction;
        
    };
    
    
    
}

#endif /* ClickObject_hpp */
