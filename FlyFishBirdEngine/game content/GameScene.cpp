//
//  GameScene.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "GameScene.hpp"


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
    
    DrawObject * draw = FFBMalloc(DrawObject);
    draw->Create();
    draw->DrawCircleAndFill(0, 0, 100);
    draw->SetColor(0, 0, 0, 1);
    m_rootObject->AddObject(draw);
    draw->release();
    
    return true;
}


void GameScene::Destory()
{
    Scene::Destory();
}

