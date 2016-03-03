//
//  ChoseScene.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "FlyFishBird.h"

#include "ChoseScene.hpp"
#include "LevelScene.hpp"
#include "GameScene.hpp"


using namespace ffb;


void ChoseScene::Clear()
{
    Scene::Clear();
}


void ChoseScene::Destory()
{
    Scene::Destory();
}


bool ChoseScene::Create()
{
    if (!Scene::Create()) {
        return false;
    }
    
    Size screenSize = GameController::GetSingletonPtr()->GetDevice()->GetScreenSize();
    
    TouchLabel * levelGame = FFBMalloc(TouchLabel);
    levelGame->Create("关卡模式", 25);
    levelGame->GetLabel()->SetTextColor(0, 0, 0, 1);
    levelGame->SetPosition(PointMake(screenSize.width/2, screenSize.height/12*7));
    levelGame->SetTouchFunction(function1st(ChoseScene::ChoseLevel, this));
    m_rootObject->AddObject(levelGame);
    levelGame->release();
    
    TouchLabel * StartGame = FFBMalloc(TouchLabel);
    StartGame->Create("无尽模式", 25);
    StartGame->GetLabel()->SetTextColor(0, 0, 0, 1);
    StartGame->SetPosition(PointMake(screenSize.width/2, screenSize.height/12*5));
    StartGame->SetTouchFunction(function1st(ChoseScene::StartGame, this));
    m_rootObject->AddObject(StartGame);
    StartGame->release();
    
    return true;
}

void ChoseScene::StartGame(ffb::Object * sender)
{
    GameScene * game = FFBMalloc(GameScene);
    game->Create(0, 1);
    GameController::GetSingletonPtr()->PushScene(game);
    game->release();
}

void ChoseScene::ChoseLevel(ffb::Object * sender)
{
    LevelScene * levelScene = FFBMalloc(LevelScene);
    levelScene->Create();
    GameController::GetSingletonPtr()->PushScene(levelScene);
    levelScene->release();
}
