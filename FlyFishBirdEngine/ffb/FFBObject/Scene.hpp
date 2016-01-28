//
//  Scene.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "BasicPtrClass.hpp"
#include "Object.hpp"

namespace ffb {
    class Scene: public BasicPtrClass {
        
    public:
        
        CreateClassFunctions(Scene);
        
        bool Create(Object * rootObject);
        
        
        // update and render object
        void render();
        void update(double dt);
        
        
        //rootObject
        Object * GetRootObject();
        
    protected:
        
        Object * m_rootObject;
        
    };

}

#endif /* Scene_hpp */
