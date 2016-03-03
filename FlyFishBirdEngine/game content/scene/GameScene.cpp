//
//  GameScene.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "FlyFishBird.h"

#include "GameScene.hpp"
#include <math.h>
#include "RepeatSprite.hpp"

using namespace ffb;

void GameScene::Clear()
{
#if FFBDEBUG
    m_design = false;
#endif
    m_mapObject = FFBMalloc(MapObject);
    Scene::Clear();
}

void GameScene::Destory()
{
    FFBSaveFree(m_mapObject);
#if !FFBDEBUG
    FFBSaveFree(m_people);
#endif
    Scene::Destory();
}

bool GameScene::Create()
{
    if (!Scene::Create()) {
        return false;
    }
    
    return true;
}

bool GameScene::Create(int level, int people)
{
    if (!Scene::Create()) {
        return false;
    }
    
    m_mapObject->Create(level);
    
    m_people = People::Create(people);
    Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
    m_people -> SetPosition(screenSize.width/2-160, screenSize.height-120);
    m_rootObject->AddObject(m_people);
    m_people -> SetFirstAngle( tan(4/3.0) );
    
    TouchLabel * label = FFBMalloc(TouchLabel);
    label->TouchLabel::Create("返回");
    label->SetPosition(PointMake(100, 100));
    label->SetTouchFunction(function0st(GameController::PopScene, GameController::GetSingletonPtr()));
    m_rootObject->AddObject(label);
    label->release();
    
#if FFBDEBUG
    m_mapObject->Create(level, false);
#else
    m_mapObject->Create(level);
#endif
    m_rootObject->AddObject(m_mapObject);
    
#if FFBDEBUG
    m_design = false;
#endif
    
    return true;
}

#if FFBDEBUG
#include "SelectSprite.hpp"

bool GameScene::CreateDesignScene(int level, int people)
{
    if (!Scene::Create()) {
        return false;
    }
    
    Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
    
    TouchLabel * add = FFBMalloc(TouchLabel);
    add->Create("添加", 30);
    add->SetPosition(screenSize.width/2-add->GetLabel()->GetSize().width, screenSize.height-add->GetLabel()->GetSize().height/2);
    add->SetTouchFunction(function0st(GameScene::AddItem, this));
    m_rootObject->AddObject(add);
    add->release();
    
    TouchLabel * cut = FFBMalloc(TouchLabel);
    cut->Create("删除", 30);
    cut->SetPosition(screenSize.width/2+cut->GetLabel()->GetSize().width, screenSize.height-cut->GetLabel()->GetSize().height/2);
    cut->SetTouchFunction(function0st(GameScene::cutItem, this));
    m_rootObject->AddObject(cut);
    cut->release();
    
    TouchLabel * label = FFBMalloc(TouchLabel);
    label->TouchLabel::Create("返回", 30);
    label->SetPosition(add->GetLabel()->GetSize().width, screenSize.height-add->GetLabel()->GetSize().height/2);
    label->SetTouchFunction(function0st(GameScene::Back, this));
    m_rootObject->AddObject(label);
    label->release();
    
    m_design = true;
    m_mapObject->Create(level, true);
    m_rootObject->AddObject(m_mapObject);
    
    
    ffb::TouchLabel * m_sure;
    ffb::TouchLabel * m_cancel;
    
    m_sure = FFBMalloc(TouchLabel);
    m_sure->Create("确定", 30);
    m_sure->SetPosition(screenSize.width/4*3, screenSize.height - m_sure->GetLabel()->GetSize().height/2);
    m_sure->SetTouchFunction(function1st(MapObject::Sure, m_mapObject));
    m_rootObject->AddObject(m_sure);
    m_sure->release();
    
    m_cancel = FFBMalloc(TouchLabel);
    m_cancel->Create("取消", 30);
    m_cancel->SetPosition(screenSize.width/4*3+m_sure->GetLabel()->GetSize().width, screenSize.height - m_cancel->GetLabel()->GetSize().height/2);
    m_cancel->SetTouchFunction(function1st(MapObject::Cancel, m_mapObject));
    m_rootObject->AddObject(m_cancel);
    m_cancel->release();

    return true;
}

void GameScene::AddItem()
{
    m_mapObject->AddTouchObject();
}

void GameScene::cutItem()
{
    m_mapObject->RemoveTouchObject();
}

void GameScene::Back()
{
#if FFBDEBUG
    printf("%s", m_mapObject->GetDesignString().c_str());
    char level[3]; IntToString(level, m_mapObject->GetLevel());
    std::string levelStr = "level_";
//    DiskCache::GetSingletonPtr()->CacheStringForKey(m_mapObject ->GetDesignString(), level + levelStr);
#endif
    GameController::GetSingletonPtr()->PopScene();
}

#endif





















