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
        }
        if (scene != nullptr) {
            PushScene(scene);
        }
        
    }
    
    Scene * GameController::GetCurrentScene()
    {
        if (m_sceneVector.empty()) {
            return nullptr;
        }
        return m_sceneVector.back();
    }
    
    void GameController::PushScene(ffb::Scene *scene)
    {
        scene->retain();
        m_sceneVector.push_back(scene);
    }
    
    void GameController::PopScene()
    {
        m_sceneVector[m_sceneVector.size()-1]->release();
        m_sceneVector.pop_back();
    }
    
    
#pragma mark - update
    
    
    void GameController::update(double dt)
    {
        TimeSchedule::GetSingletonPtr()->Update(dt);
        
        Scene * currentScene = GetCurrentScene();
        if (currentScene) {
            currentScene->update(dt);
        }
        
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        if (currentScene) {
            currentScene->render();
        }
        PoolManager::GetSingletonPtr()->GetMainPool()->Clear();

    }
    
    
    
#pragma mark - touch

    
}





