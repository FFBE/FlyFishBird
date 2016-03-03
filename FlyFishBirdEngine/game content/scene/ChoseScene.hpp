//
//  ChoseScene.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef ChoseScene_hpp
#define ChoseScene_hpp

#include <stdio.h>
#include "Scene.hpp"

class ChoseScene: public ffb::Scene {
    
    
    
public:
    
    CreateClassFunctions(ChoseScene);
    
    void ChoseLevel(ffb::Object * sender);
    void StartGame(ffb::Object * sender);
    
    
private:
    
    
};



#endif /* GameScene_hpp */
