//
//  Object.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Object.hpp"


namespace ffb {
    
#pragma mark - Touch
    
    CreateSimpleClass(Touch, BasicPtrClass);
    
    bool Touch::Create(Point point, double timestamp)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        m_point = point;
        m_touchTimestamp = timestamp;
        return true;
    }
    
    Point Touch::ConverTouchPointToObject(ffb::Object *object)
    {
        return PointMake(m_point.x-object->m_renderer->GetPosition().x, m_point.y-object->m_renderer->GetPosition().y);
    }
    
    
#pragma mark - Object
    
    void Object::Clear()
    {
        BasicPtrClass::Clear();
        m_renderer = nullptr;
        m_supObject = nullptr;
        m_position = PointMake(0, 0);
        m_scale = PointMake(1, 1);
        m_rotate = 0;
        m_touchEnable = true;
        m_tag = 0;
        m_hidden = false;
    }
    
    void Object::Destory()
    {
        FFBSaveFree(m_renderer);
        RemoveAllObject();
        BasicPtrClass::Destory();
    }

    bool Object::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_renderer = FFBMalloc(Renderer);

        return true;
    }
    
    bool Object::Create(Renderer * render)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        SetRenderer(render);
        
        return true;
    }
    
#pragma mark - object
    
    void Object::SetTag(int tag)
    {
        m_tag = tag;
    }
    
    int Object::GetTag()
    {
        return m_tag;
    }
    
    void Object::AddObject(ffb::Object *object)
    {
        object->m_supObject = this;
        object->retain();
        m_objectList.push_back(object);
    }
    
    void Object::RemoveObject(ffb::Object *object)
    {
        if (object == nullptr) {
            return;
        }
        
        ObjectList::iterator itera;
        for (itera = m_objectList.begin(); itera != m_objectList.end(); ) {
            if ( (*itera) == object) {
                object->m_supObject = nullptr;
                object->release();
                m_objectList.erase(itera);
            }
            else
                ++itera;
        }
    }
    
    void Object::RemoveAllObject()
    {
        if (m_objectList.empty()) {
            return;
        }
        
        ObjectList::iterator itera;
        
        for (itera = m_objectList.begin(); itera != m_objectList.end(); ) {
            (*itera)->release();
            m_objectList.erase(itera);
        }
        
        m_objectList.clear();
    }
    
    void Object::RemoveFromSuperObject()
    {
        m_supObject->RemoveObject(this);
    }
    
    
    void Object::SetRenderer(ffb::Renderer * renderer)
    {
        if (m_renderer != nullptr) {
            m_renderer->release();
        }
        
        m_renderer = renderer;
        m_renderer->retain();
    }
    
    Renderer * Object::GetRenderer()
    {
        return m_renderer;
    }
    
    
#pragma mark - transform
    
    
    //postion
    void Object::SetPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
    }
    
    Point Object::GetPosition()
    {
        return m_position;
    }
    
    void Object::SetPosition(Point point)
    {
        m_position = point;
    }
    
    //scale
    void Object::SetScale(Point scale)
    {
        m_scale = scale;
    }
    
    void Object::SetScale(float x, float y)
    {
        m_scale.x = x;
        m_scale.y = y;
    }
    
    void Object::SetScale(float scale)
    {
        m_scale.x = scale; m_scale.y = scale;
    }
    
    Point Object::GetScale()
    {
        return m_scale;
    }
    
    
    //rotate
    void Object::SetRotate(float angle)
    {
        m_rotate = angle;
    }
    
    float Object::GetRotate()
    {
        return m_rotate;
    }
    
    
    // hidden
    void Object::SetHidden(bool hidden)
    {
        m_hidden = hidden;
    }
    
    bool Object::GetHidden()
    {
        return m_hidden;
    }
    
    
#pragma mark - action
    
    void Object::AddAction(ffb::Action *action)
    {
        action->m_actionObject = this;
        action->Start();
        ActionManager::GetSingletonPtr()->AddAction(action);
    }
    
    void Object::RemoveAction(ffb::Action *action)
    {
        ActionManager::GetSingletonPtr()->RemoveAction(action);
    }
    
    void Object::RemoveActionByTag(int tag)
    {
        ActionManager::GetSingletonPtr()->RemoveAction(this, tag);
    }
    
    
#pragma mark - render 
    
    void Object::Render()
    {
        float supMeshRotate = 0;
        Point supMeshPostion = PointMake(0, 0);
        Point supMeshScale = PointMake(1, 1);
        
        if (m_supObject != nullptr) {
            supMeshPostion = PointMake(m_supObject->m_renderer->GetPosition().x, m_supObject->m_renderer->GetPosition().y);
            supMeshScale = PointMake(m_supObject->m_renderer->GetScale().x, m_supObject->m_renderer->GetScale().y);
            supMeshRotate = m_supObject->m_renderer->GetRotate();
        }
        
        m_renderer->SetPosition(supMeshPostion.x+m_position.x, supMeshPostion.y+m_position.y);
        m_renderer->SetScale(supMeshScale.x*m_scale.x, supMeshScale.y*m_scale.y);
        m_renderer->SetRotate(supMeshRotate+m_rotate);
        m_renderer->Render();
        
        if (m_objectList.empty()) {
            return;
        }
        
        ObjectList::iterator itera;
        Object * object;
        for (itera=m_objectList.begin(); itera != m_objectList.end(); itera++) {
            object = (Object *)(*itera);
            if (!m_hidden) {
                object->Render();
            }
        }
    }
    
    void Object::Update(double dt)
    {
        if (m_objectList.empty()) {
            return;
        }
        
        ObjectList::iterator itera;
        Object * object ;
        for (itera = m_objectList.begin(); itera != m_objectList.end(); itera++) {
            object = (Object *)(*itera);
            object->Update(dt);
        }
    }
    
    
#pragma mark - touch
    
    void Object::SetTouchEnable(bool touchEnable)
    {
        m_touchEnable = touchEnable;
    }
    
    bool Object::GetTouchEnable()
    {
        return m_touchEnable;
    }
    
    bool Object::TouchShouldBegin(Touch * touch)
    {
        return false;
    }
    
    void Object::TouchMoved(Touch * touch)
    {
    }
    
    void Object::TouchEnd(Touch * touch)
    {
    }
    
    Object * Object::TouchCheck(Touch * touch)
    {
        if (!m_touchEnable) {
            return nullptr;
        }
        
        if (TouchShouldBegin(touch)) {
            return this;
        }
        
        if (m_objectList.empty()) {
            return nullptr;
        }
        
        ObjectList::iterator itera;
        Object * object;
        for (itera = m_objectList.begin(); itera != m_objectList.end(); itera++)
        {
            object = *itera;
            Object * touchObject = object->TouchCheck(touch);
            if (touchObject != nullptr) {
                return touchObject;
            }
        }
        return nullptr;
    }
}

