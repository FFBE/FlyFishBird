//
//  Object.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Object.hpp"

namespace ffb {
    
    void Object::Clear()
    {
        BasicPtrClass::Clear();
        m_mesh = nullptr;
        m_supObject = nullptr;
        m_position = PointMake(0, 0);
        m_scale = PointMake(1, 1);
        m_rotate = 0;
    }
    
    bool Object::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_mesh = FFBMalloc(Mesh);
        m_mesh->Create();
        
        return true;
    }
    
    bool Object::Create(Mesh * mesh)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        mesh->retain();
        m_mesh = mesh;
        
        return true;
    }
    
    void Object::Destory()
    {
        FFBMustFree(m_mesh);
        m_supObject = nullptr;
        BasicPtrClass::Destory();
    }
    
    void Object::AddObject(ffb::Object *object)
    {
        object->m_supObject = this;
        object->retain();
        m_objectList.push_back(object);
    }
    
    
    void Object::RemoveObject(ffb::Object *object)
    {
        ObjectList::iterator itera;
        for (itera = m_objectList.begin(); itera != m_objectList.end(); ) {
            if ( (*itera) == object) {
                (*itera)->release();
                m_objectList.erase(itera);
            }
            else
                ++itera;
        }
    }
    
    
    
    
    
#pragma mark - position
    
    
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
    
    
    //background
    void Object::SetColor(float r, float g, float b, float a)
    {
        m_mesh->SetColor(r, g, b, a);
    }
    
    void Object::SetColor(Color color)
    {
        m_mesh->SetColor(color);
    }
    
    Color Object::GetColor()
    {
        return m_mesh->GetColor();
    }
    
    
#pragma mark - render 
    
    void Object::Render()
    {
        float supMeshRotate = 0;
        Point supMeshPostion = PointMake(0, 0);
        Point supMeshScale = PointMake(1, 1);
        if (m_supObject != nullptr) {
            supMeshPostion = PointMake(m_supObject->m_mesh->GetPosition().x, m_supObject->m_mesh->GetPosition().y);
            supMeshScale = PointMake(m_supObject->m_mesh->GetScale().x, m_supObject->m_mesh->GetScale().y);
            supMeshRotate = m_supObject->m_mesh->GetRotate();
        }
        
        m_mesh->SetPosition(supMeshPostion.x+m_position.x, supMeshPostion.y+m_position.y);
        m_mesh->SetScale(supMeshScale.x*m_scale.x, supMeshScale.y*m_scale.y);
        m_mesh->SetRotate(supMeshRotate+m_rotate);
        
        m_mesh->Render();
        
        if (m_objectList.empty()) {
            return;
        }
        ObjectList::iterator itera;
        for (itera=m_objectList.begin(); itera != m_objectList.end(); itera++) {
            Object * object = (Object *)(*itera);
            object->Render();
        }
    }
    
    void Object::update(double dt)
    {
        if (m_objectList.empty()) {
            return;
        }
        
        ObjectList::iterator itera;
        for (itera=m_objectList.begin(); itera != m_objectList.end(); itera++) {
            Object * object = (Object *)(*itera);
            object->update(dt);
        }
    }
    
}

