//
//  FFBGLESController.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GameController.hpp"
#include <iostream>

#include "Macro.h"
#include "ResourceManager.hpp"
#include "AutoReleasePool.hpp"
#include "TimeSchedule.hpp"
#include "Sprite.hpp"
#include "Action.hpp"

namespace ffb {
    
#define InsertProgramMapType(key, value) std::map< short, GLESProgram *>::value_type(key, value)

    
    GameController::GameController()
    {
        m_device = Device::GetSingletonPtr();
    }
    
    GameController::~GameController()
    {
    
    }
    
    const Matrix GameController::GetCameraMatrix()
    {
        return m_camera.GetCameraMatrix();
    }
    
    
    
    
    
#pragma mark - GL Program Manager
    
    void GameController::SetGLVersion(float version)
    {
        m_glVersion = version;
    }
    
    float GameController::GetGLVersion()
    {
        return m_glVersion;
    }
    
    const ESProgramMap GameController::GetProgramMap()
    {
        return m_renderPrograms;
    }
    
    void GameController::AddProgram(GLESProgram *Program, short key)
    {
        GLESProgram * pro = nullptr;
        ESProgramMap::iterator itera;
        
        if (!m_renderPrograms.empty()) {
            
            itera = m_renderPrograms.find(key);
            
            if (itera != m_renderPrograms.end()){
                
                pro = (GLESProgram *)(*itera).second;
            }
        }
        
        if (pro != nullptr) {
            return;    
        }
        
        Program->retain();
        m_renderPrograms.insert(InsertProgramMapType(key, Program));
    }
    
    GLESProgram * GameController::GetProgramWithKey(short key)
    {
        if (m_renderPrograms.empty()) {
            return nullptr;
        }
        
        ESProgramMap::iterator itera;
        itera = m_renderPrograms.find(key);
        if (itera == m_renderPrograms.end()) {
            return nullptr;
        }
        
        return (GLESProgram *)(*itera).second;
    }
    
    void GameController::RemoveProgramWithKey(short key)
    {
        FFBAssert( key!=defaultProgram, "key cannot be defaultProgram" );
        if (m_renderPrograms.empty())
        {
            printf("have not render Program");
            return;
        }
        
        ESProgramMap::iterator itera;
        
        itera = m_renderPrograms.find(key);
        if (itera != m_renderPrograms.end()) {
            
            GLESProgram * Program = (GLESProgram *)(*itera).second;
            Program->release();
            m_renderPrograms.erase(itera);
        }
        else {
            std::cout<<"Program "<<key<<" not find"<<std::endl;
        }
    }
    
    
    
   
    
#pragma mark - 
    
    Device * GameController::GetDevice()
    {
        return m_device;
    }
    
    void GameController::LoadDefaultProgram()
    {
        GLESProgram * program = FFBMalloc(GLESProgram);
        program->Create();
        AddProgram(program, defaultProgram);
        program->release();
    }
    
    void GameController::LoadCamera()
    {
        float scale = m_device->GetScreenScale();
        float width = m_device->GetScreenWidth();
        float height = m_device->GetScreenHeight();
        m_camera.Create();
        m_camera.CameraOrtho(-width/2*scale, width/2*scale, -height/2*scale, height/2*scale, 0.0f, 1000.0f);
        glViewport(0, 0, width*scale, height*scale);
    }
    
    
    
#pragma mark - Scene Manager
    
    void GameController::SetRootScene(ffb::Scene *scene)
    {
        if (!m_sceneVector.empty()) {
            for (Scene * sc : m_sceneVector)
            {
                sc->release();
            }
            m_sceneVector.clear();
        }
        if (scene != nullptr) {
            scene->retain();
            m_sceneVector.push_back(scene);
        }
        LoadLaunchImage();
    }
    
    void GameController::LoadLaunchImage()
    {
        Sprite * launchImage = FFBMalloc(Sprite);
        launchImage->CreateLaunchImageForApple();
        launchImage->SetPosition(PointMake(m_device->GetScreenWidth()/2, m_device->GetScreenHeight()/2));
        GetCurrentScene()->GetRootObject()->AddObject(launchImage);
        TimeSchedule::GetSingletonPtr()->AddSchedule(function0st(Object::RemoveFromSuperObject, launchImage), 3.0);
        launchImage->release();
    }
    
    Scene * GameController::GetCurrentScene()
    {
        FFBAssert(!m_sceneVector.empty(), "scene connot be empty");
        
        return m_sceneVector.back();
    }
    
    void GameController::PushScene(ffb::TransformScene *scene)
    {
        scene->retain();

        scene->SceneStartPush();
        double time = scene->PushAction();
        
        scene->SetSubScene(GetCurrentScene());
        m_sceneVector.push_back(scene);
        
        TimeSchedule::GetSingletonPtr()->AddSchedule(function0st(TransformScene::SceneEndPush, scene), time);
    }
    
    void GameController::PopScene()
    {
        FFBAssert(!m_sceneVector.empty(), "scene cannot be empty");
        
        TransformScene * scene = static_cast<TransformScene *>( m_sceneVector.back() );
        
        scene->SceneStartPop();
        double time = scene->PopAction();
        
        TimeSchedule::GetSingletonPtr()->AddSchedule(function0st(TransformScene::SceneEndPop, scene), time);
    }
    
    
#pragma mark - update
    
    
    void GameController::Update(double dt)
    {
        //update action
        ActionManager::GetSingletonPtr()->Update(dt);
        
        //update time schedule
        TimeSchedule::GetSingletonPtr()->Update(dt);
        
        //update object
        Scene * currentScene = GetCurrentScene();
        currentScene->Update(dt);
        
#if FFBDEBUG
//        if (dt > 0.02) {
//            printf("%f", dt);
//        }
#endif
        
        // render
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        if (currentScene) {
            currentScene->Render();
        }
        
        // clear autorelease pool
        PoolManager::GetSingletonPtr()->GetMainPool()->Clear();

    }
    
    
    
#pragma mark - touch

    
}





