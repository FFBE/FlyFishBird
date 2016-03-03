//
//  GameScene.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "Scene.hpp"
#include "People.hpp"
#include <string>
#include "MapObject.hpp"

class GameScene:public ffb::RightToLeftScene  {
    
    
#if FFBDEBUG
    
private:
    
    bool m_design;
    void AddItem();
    void cutItem();
    
public:
    bool CreateDesignScene(int level, int people);
    
#endif
    
public:
    
    CreateClassFunctions(GameScene);
    bool Create(int level ,int people);
    
    void Back();
    
private:
    
    People * m_people;
    std::string m_fileContent;
    MapObject * m_mapObject;
    
};

#endif /* GameScene_hpp */
