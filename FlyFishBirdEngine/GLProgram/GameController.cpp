//
//  FFBGLESController.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GameController.hpp"
#include "Define.h"
#include <iostream>

namespace ffb {
    
    GameController::GameController():m_rootScene(nullptr), m_screenSize(SizeMake(0, 0))
    {
        
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
    
    
    
   
    
#pragma mark - GL Screen Manager
    
    void GameController::SetScreenSize(float width, float height)
    {
        m_screenSize.width = width;
        m_screenSize.height = height;
        
        m_camera.Create();
        m_camera.CameraOrtho(-width/2*m_scale, width/2*m_scale, -height/2*m_scale, height/2*m_scale, 0.0f, 1000.0f);
        glViewport(0, 0, width*m_scale, height*m_scale);

        GLESProgram * Program = FFBMalloc(GLESProgram);
        Program->Create();
        AddProgram(Program, defaultProgram);
        Program->release();
    }
    
    void GameController::SetScreenScale(float scale)
    {
        m_scale = scale;
    }
    
    float GameController::GetScreenScale()
    {
        return m_scale;
    }
    
    float GameController::GetScreenWidth()
    {
        return m_screenSize.width;
    }
    
    float GameController::GetScreenHeight()
    {
        return m_screenSize.height;
    }

    Size GameController::GetScreenSize()
    {
        return m_screenSize;
    }
    
    
    
#pragma mark - Scene Manager
    
    void GameController::SetRootScene(ffb::Scene *scene)
    {
        if (m_rootScene != nullptr) {
            m_rootScene->release();
        }
        scene->retain();
        m_rootScene = scene;
    }
    
    Scene * GameController::GetRootScene()
    {
        return m_rootScene;
    }
    
    
    
    
    
#pragma mark - update
    
    void GameController::render()
    {
        glViewport(0, 0, m_screenSize.width * m_scale, m_screenSize.height * m_scale);
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (m_rootScene != nullptr) {
            m_rootScene->render();
        }
    }
    
    void GameController::update(double dt)
    {
        if (m_rootScene != nullptr) {
            m_rootScene->update(dt);
        }
    }
    
    
    
    
    
    
}





