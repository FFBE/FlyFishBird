//
//  LevelScene.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include <stdio.h>
#include "Scene.hpp"
#include "TouchObject.hpp"

class LevelScene:public ffb::RightToLeftScene {
    
    
public:
    
    CreateClassFunctions(LevelScene);
    
    void ChoseLevel(ffb::TouchObject * object);
    
#ifdef FFBDEBUG
    
    void PlayGame(ffb::TouchObject * object);
    void DesignGame(ffb::TouchObject * object);
    
private:
    
    ffb::Object * m_choseObject;
    ffb::Scroll * m_scroll;
    
#endif
    
};

#endif /* LevelScene_hpp */
