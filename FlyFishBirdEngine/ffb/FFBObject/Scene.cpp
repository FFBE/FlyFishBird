//
//  Scene.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Scene.hpp"
#include "Macro.h"
#include "GameController.hpp"

namespace ffb {
    
    void Scene::Clear()
    {
        m_rootObject = nullptr;
    }

    bool Scene::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        Size screenSize = GameController::GetSingletonPtr()->GetDevice()->GetScreenSize();
        Renderer * render = FFBMalloc(Renderer);
        render->Create();
        m_rootObject = FFBMalloc(Object);
        m_rootObject->Create(render);
        m_rootObject->SetPosition(PointMake(-screenSize.width/2, -screenSize.height/2));
        
        return true;
    }
    
    void Scene::Destory()
    {
        FFBSaveFree(m_rootObject);
        
        BasicPtrClass::Destory();
    }
    
    
    Object * Scene::GetRootObject()
    {
        return m_rootObject;
    }
    
    Object * Scene::GetTouchObject()
    {
        return m_touchObject;
    }
    
    void Scene::SetTouchObject(ffb::Object *touchObject)
    {
        m_touchObject = touchObject;
    }
    
    
    void Scene::render()
    {
        m_rootObject->Render();
    }
    
    void Scene::update(double dt)
    {
        m_rootObject->update(dt);
    }
    
    
}