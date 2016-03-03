//
//  LevelScene.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "FlyFishBird.h"

#include "LevelScene.hpp"
#include "GameScene.hpp"

#define LevelCount          8
#define LevelSpriteWidth    425

#define ScaleInIphone4      0.8

using namespace ffb;

void LevelScene::Clear()
{
    Scene::Clear();
}

void LevelScene::Destory()
{
    Scene::Destory();
}

bool LevelScene::Create()
{
    if (!Scene::Create()) {
        return false;
    }
    
    Size screen = Device::GetSingletonPtr()->GetScreenSize();
    
    Sprite * background = FFBMalloc(Sprite);
    background->Create("level_background");
    background->SetPosition(screen.width/2, screen.height/2);
    m_rootObject->AddObject(background);
    background->release();
    
    m_scroll = FFBMalloc(Scroll);
    if (screen.width == 480) {
        m_scroll->Create(SizeMake(LevelSpriteWidth*ScaleInIphone4, screen.height), SizeMake(LevelSpriteWidth*ScaleInIphone4, LevelCount/4.0*screen.height));
    }
    else
        m_scroll->Create(SizeMake(LevelSpriteWidth, screen.height), SizeMake(screen.width-100, LevelCount/4.0*screen.height));

    m_scroll->SetPosition(0, screen.height);
    
    for (int i = 1; i<=LevelCount; i++) {
        
//        char number[3];
        
//        sprintf(number, "%d", i);
        
        std::string fileName = "level_1";
//        fileName += number;
        
        TouchSprite * sprite = FFBMalloc(TouchSprite);
        sprite->Create(fileName);
        sprite->SetTag(i);
        sprite->SetTouchFunction(function1st(LevelScene::ChoseLevel, this));
        
        if (screen.width == 480) {
            sprite->GetSprite()->SetScale(ScaleInIphone4);
            sprite->SetPosition(sprite->GetSprite()->GetSize().width/2*ScaleInIphone4, screen.height/8*(2*i-1));
        }
        else
            sprite->SetPosition(sprite->GetSprite()->GetSize().width/2, screen.height/8*(2*i-1));
        
        m_scroll->AddObjectToScroll(sprite);
        sprite->release();
    }
    
    m_rootObject->AddObject(m_scroll);
    
    m_scroll->release();
    
    TouchSprite * back = FFBMalloc(TouchSprite);
    back->Create("level_back");
    back->SetPosition(screen.width - back->GetSprite()->GetSize().width/2, 237);
    back->SetTouchFunction(function0st(GameController::PopScene, GameController::GetSingletonPtr()));
    m_rootObject->AddObject(back);
    back->release();
    
    TouchSprite * settingButton = FFBMalloc(TouchSprite);
    settingButton->Create("level_setting");
    settingButton->SetPosition(screen.width - settingButton->GetSprite()->GetSize().width/2, 85);
    m_rootObject->AddObject(settingButton);
    settingButton->release();
    
    return true;
}

void LevelScene::ChoseLevel(TouchObject * object)
{
#if !FFBDEBUG

    GameScene * gameScene = FFBMalloc(GameScene);
    gameScene->Create(object->GetTag(), 1);
    GameController::GetSingletonPtr()->PushScene(gameScene);
#else
    m_scroll->SetTouchEnable(false);
    
    Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
    
    m_choseObject = FFBMalloc(Object);
    m_choseObject->Create();
    m_choseObject->SetPosition(screenSize.width/2, screenSize.height/2);
    
    TouchLabel * designGame = FFBMalloc(TouchLabel);
    designGame->SetTag(object->GetTag());
    designGame->Create("设计", 50);
    designGame->GetLabel()->SetTextColor(0, 0, 0, 1);
    designGame->SetPosition(PointMake(0, screenSize.height/6));
    designGame->SetTouchFunction(function1st(LevelScene::DesignGame, this));
    m_choseObject->AddObject(designGame);
    designGame->release();
    
    TouchLabel * playGame = FFBMalloc(TouchLabel);
    playGame->SetTag(object->GetTag());
    playGame->Create("试玩", 50);
    playGame->GetLabel()->SetTextColor(0, 0, 0, 1);
    playGame->SetPosition(PointMake(0, -screenSize.height/6));
    playGame->SetTouchFunction(function1st(LevelScene::PlayGame, this));
    m_choseObject->AddObject(playGame);
    playGame->release();
    
    m_rootObject->AddObject(m_choseObject);
}

void LevelScene::PlayGame(ffb::TouchObject *object)
{
    GameScene * gameScene = FFBMalloc(GameScene);
    gameScene->Create(object->GetTag(), 1);
    GameController::GetSingletonPtr()->PushScene(gameScene);
    gameScene->release();
    
    m_scroll->SetTouchEnable(true);
    m_choseObject->RemoveFromSuperObject();
    m_choseObject->release();
}

void LevelScene::DesignGame(ffb::TouchObject *object)
{
    GameScene * gameScene = FFBMalloc(GameScene);
    gameScene->CreateDesignScene(object->GetTag(), 1);
    GameController::GetSingletonPtr()->PushScene(gameScene);
    gameScene->release();
    
    m_scroll->SetTouchEnable(true);
    m_choseObject->RemoveFromSuperObject();
    m_choseObject->release();
#endif
}

