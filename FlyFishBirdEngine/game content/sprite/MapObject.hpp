//
//  DesignRootObject.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/29.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef MapObject_hpp
#define MapObject_hpp

#include <stdio.h>
#include "FlyFishBird.h"
#include "GameLevelAnalysis.hpp"


class MapObject : public ffb::Object {
    
    
    
    
public:
    

    
    
    
    CreateClassFunctions(MapObject);
    bool Create(int level);
    
    int GetLevel();
    
#if FFBDEBUG

    bool Create(int level, bool design);
    
    TouchEventFuncation;
    
    void AddTouchObject();
    void RemoveTouchObject();
    
    void Sure(ffb::TouchObject * object);
    void Cancel(ffb::TouchObject * object);
    
    std::string GetDesignString();
    
protected:
    
    void TouchObjectCannotTouch();
    
    void SpriteBeenTouch(ffb::TouchObject * object); 
    
private:
    
    ffb::TextInput * m_textInput;
    
    bool m_subObjectCanRespond;
    
    ffb::Point m_lastTouchPoint;
    
    ffb::Object * m_choseObject;
    GameItems::iterator m_choseGameItem;
    
    float m_lastx;
            
#endif
private:
    
    GameItems m_gameItems;
    int  m_level;
};

#endif /* DesignRootObject_hpp */
