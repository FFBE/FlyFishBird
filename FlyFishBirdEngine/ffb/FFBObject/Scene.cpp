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
#include "SimpleRender.hpp"

namespace ffb {
    
    void Scene::Clear()
    {
        
        BasicPtrClass::Clear();
    }
    
    
    void Scene::Destory()
    {
        FFBSaveFree(m_rootObject);
        BasicPtrClass::Destory();
    }

    bool Scene::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        Size screenSize = GameController::GetSingletonPtr()->GetDevice()->GetScreenSize();
        float scale = Device::GetSingletonPtr()->GetScreenScale();
        
        GLuint indices[] = {1, 2, 4, 3};
        GLfloat vertices[] = {0, 0, screenSize.width*scale, 0, screenSize.width*scale, screenSize.height*scale, 0, screenSize.height*scale};
        
        m_rootObject = FFBMalloc(Object);

        SimpleRender * render = FFBMalloc(SimpleRender);
        render->Create(4, 4, indices, vertices, FFBDrawTypeTriangle_Strip, VerticesStepTwo);
        m_rootObject->Create(render);
        m_rootObject->SetPosition(PointMake(-screenSize.width/2, -screenSize.height/2));
        
        return true;
    }
    
    bool Scene::Create(ffb::Object *rootObject)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        Size screenSize = GameController::GetSingletonPtr()->GetDevice()->GetScreenSize();

        m_rootObject = rootObject;
        rootObject->retain();
        m_rootObject->SetPosition(PointMake(-screenSize.width/2, -screenSize.height/2));
        
        return true;
    }
    
    void Scene::CheckTouchObject(Touch * touch)
    {
        m_touchObject = m_rootObject->TouchCheck(touch);
    }
    
    Object * Scene::GetRootObject()
    {
        return m_rootObject;
    }
    
    Object * Scene::GetTouchObject()
    {
        return m_touchObject;
    }

    void Scene::ResetTouchObject()
    {
        m_touchObject = nullptr;
    }
    
    void Scene::SetColor(float r, float g, float b, float a)
    {
        SimpleRender * render = static_cast<SimpleRender *>( m_rootObject->GetRenderer() );
        render->SetColor(r, g, b, a);
    }
    
    void Scene::SetColor(Color color)
    {
        SimpleRender * render = static_cast<SimpleRender *>( m_rootObject->GetRenderer() );
        render->SetColor(color);
    }
    
    Color Scene::GetColor()
    {
        SimpleRender * render = static_cast<SimpleRender *>( m_rootObject->GetRenderer() );
        return render->GetColor();
    }
    
    
    void Scene::Render()
    {
        m_rootObject->Render();
    }
    
    void Scene::Update(double dt)
    {
        m_rootObject->Update(dt);
    }
    
    
#pragma mark - TransformScene
    
#define CreateSimpleScene(Class)    CreateSimpleClass(Class, TransformScene)
    
    void TransformScene::Clear()
    {
        m_transformTime = 0.3;
        Scene::Clear();
    }
    
    void TransformScene::Destory()
    {
        Scene::Destory();
    }
    
    bool TransformScene::Create()
    {
        if (!Scene::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool TransformScene::Create(float transformTime)
    {
        if (!Scene::Create()) {
            return false;
        }
        
        m_transformTime = transformTime;
        
        return true;
    }
    
    void TransformScene::SetSubScene(ffb::Scene *subScene)
    {
        m_subScene = subScene;
    }
    
    void TransformScene::Render()
    {
        FFBAssert(m_subScene, "sub scene cannot be null");
        m_subScene->Render();
        
        m_rootObject->Render();
    }
    
#pragma mark - scene live
    
    void TransformScene::SceneStartPush()
    {
        m_shouldRenderSubScene = true;
    }
    
    double TransformScene::PushAction()
    {
        return 0;
    }
    
    void TransformScene::SceneEndPush()
    {
        m_shouldRenderSubScene = false;
    }
    
    void TransformScene::SceneStartPop()
    {
        m_shouldRenderSubScene = true;
    }
    
    double TransformScene::PopAction()
    {
        return 0;
    }
    
    void TransformScene::SceneEndPop()
    {
        GameController::GetSingletonPtr()->m_sceneVector.pop_back();
        m_shouldRenderSubScene = false;
        release();
    }

#pragma mark - RightToLeftScene
    
    CreateSimpleScene(RightToLeftScene);
    
    double RightToLeftScene::PushAction()
    {
        Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
        m_rootObject->SetPosition(screenSize.width/2, -screenSize.height/2);
        
        MoveLineBy * action = FFBMalloc(MoveLineBy);
        action->Create(PointMake(-screenSize.width, 0), m_transformTime);
        m_rootObject->AddAction(action);
        
        return m_transformTime;
    }
    
    double RightToLeftScene::PopAction()
    {
        Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
        
        MoveLineBy * action = FFBMalloc(MoveLineBy);
        action->Create(PointMake(screenSize.width, 0), m_transformTime);
        m_rootObject->AddAction(action);
        
        return m_transformTime;
    }
    
}