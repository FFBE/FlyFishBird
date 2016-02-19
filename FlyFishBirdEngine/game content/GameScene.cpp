//
//  GameScene.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "GameScene.hpp"
#include "TouchTestObject.hpp"

using namespace ffb;


void GameScene::Clear()
{
    Scene::Clear();
}


bool GameScene::Create()
{
    if (!Scene::Create()) {
        return false;
    }
    
    Size screenSize = GameController::GetSingletonPtr()->GetDevice()->GetScreenSize();
    
    Label * startGame = FFBMalloc(Label);
    startGame->Create("开始游戏", 30);
    m_rootObject->AddObject(startGame);
    startGame->SetColor(1, 0, 0, 1);
    startGame->SetPosition(PointMake(screenSize.width/2, screenSize.height/2));
    startGame->release();
    
    TouchTestObject * touchTest = FFBMalloc(TouchTestObject);
    touchTest->Create();
    m_rootObject->AddObject(touchTest);
    touchTest->release();
    
    return true;
}


void GameScene::Destory()
{
    Scene::Destory();
}

