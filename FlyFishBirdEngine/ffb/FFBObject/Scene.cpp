//
//  Scene.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Scene.hpp"
#include "Macro.h"

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
        Renderer * render = FFBMalloc(Renderer);
        render->Create();
        Object * object = FFBMalloc(Object);
        object->Create(render);
        m_rootObject = (Object *)object->retain();
        
        object -> release();
        
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
    
    
    
    void Scene::render()
    {
        m_rootObject->Render();
    }
    
    void Scene::update(double dt)
    {
        m_rootObject->update(dt);
    }
}