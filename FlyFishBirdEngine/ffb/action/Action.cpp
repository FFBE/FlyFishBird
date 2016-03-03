//
//  Action.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/23.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Action.hpp"
#include "Object.hpp"

namespace ffb {
    
#define CreateSimpleAction( Class )     CreateSimpleClass(Class, Action)
    
#define CreateSimpleMoveAction( Class )     CreateSimpleClass(Class, MoveAction)

    
#pragma mark - Action
    
    void Action::Clear()
    {
        m_shouldAction = true;
        m_tag = 0;
        BasicPtrClass::Clear();
    }
    
    void Action::Destory()
    {
        BasicPtrClass::Destory();
    }
    
    bool Action::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        return true;
    }
    
    
#pragma mark - MoveAction
    
    CreateSimpleAction(MoveAction);
    
    void MoveAction::Update(double dt)
    {
        m_time -= dt;
        
        float x = dt * m_distancePerSecond.x + m_actionObject->GetPosition().x;
        float y = dt * m_distancePerSecond.y + m_actionObject->GetPosition().y;
        
        m_actionObject->SetPosition(x, y);
        
        if (m_time <= 0 ) {
            m_actionObject->SetPosition(m_endPoint);
            ActionManager::GetSingletonPtr()->RemoveAction(this);
        }
    }
    
    
#pragma mark - MoveLineTo
    
    CreateSimpleMoveAction(MoveLineTo);
    
    bool MoveLineTo::Create(Point toPoint, float time)
    {
        if (!Action::Create()) {
            return false;
        }
        
        m_endPoint = toPoint;
        m_time = time;
        
        return true;
    }
    
    void MoveLineTo::Start()
    {
        Point startPoint = m_actionObject->GetPosition();
        float distancePerSecondx = (m_endPoint.x - startPoint.x)/m_time;
        float distancePerSecondy = (m_endPoint.y - startPoint.y)/m_time;
        
        m_distancePerSecond = PointMake(distancePerSecondx, distancePerSecondy);
    }
    
   
    
    
#pragma mark - MoveLineBy
    
    CreateSimpleMoveAction(MoveLineBy);
    
    bool MoveLineBy::Create(Point byPoint, float time)
    {
        if (!MoveAction::Create()) {
            return false;
        }
        
        m_endPoint = byPoint;
        m_time = time;
        
        return true;
    }
    
    void MoveLineBy::Start()
    {
        float distancePerSecondx = m_endPoint.x/m_time;
        float distancePerSecondy = m_endPoint.y/m_time;
        
        m_distancePerSecond = PointMake(distancePerSecondx, distancePerSecondy);
        
        Point startPoint = m_actionObject->GetPosition();
        m_endPoint = PointMake(m_endPoint.x + startPoint.x, m_endPoint.y + startPoint.y);
    }
    
    
    
#pragma mark - Blink
    
    CreateSimpleClass(Blink, Action);
    
    bool Blink::Create(float perTime)
    {
        if (!Action::Create()) {
            return false;
        }
        
        m_perTime = perTime;
        m_time = 0;
        m_allTime = 1000000000000000;
        
        return true;
    }
    
    bool Blink::Create(float allTime, float times)
    {
        if (!Action::Create()) {
            return false;
        }
        
        m_perTime = allTime/times/2;
        m_time = 0;
        m_allTime = allTime;
        
        return true;
    }
    
    void Blink::Update(double dt)
    {
        if (m_time <= 0 ) {
            m_time = m_perTime;
            m_actionObject->SetHidden(!m_actionObject->GetHidden());
        }
        m_time -= dt;
        m_allTime -= dt;
        if (m_time <= 0) {
            ActionManager::GetSingletonPtr()->RemoveAction(this);
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
#pragma mark - ActionManager
    
    void ActionManager::AddAction(ffb::Action *action)
    {
        if (!m_actions.empty()) {
            bool find = false;
            for (Action * a:m_actions)
            {
                if (a == action) {
                    find = true;
                    break;
                }
            }
            if (find) {
                return;
            }
        }
        
        action->retain();
        m_actions.push_back(action);
    }
    
    void ActionManager::RemoveAction(ffb::Action *action)
    {
        if (m_actions.empty()) {
            return;
        }
        
        ActionVector::iterator itera = m_actions.begin();
        while (itera != m_actions.end()) {
            if (*itera == action) {
                action->release();
                m_actions.erase(itera);
            }
            else
                itera++;
        }
    }
    
    void ActionManager::RemoveAction(ffb::Object *object, int tag)
    {
        if (m_actions.empty()) {
            return;
        }
        
        ActionVector::iterator itera = m_actions.begin();
        while (itera != m_actions.end()) {
            
            Action * action = *itera;
            
            if (action->m_actionObject == object && action->m_tag == tag) {
                action->release();
                m_actions.erase(itera);
            }
            else
                itera++;
        }
    }
    
    void ActionManager::RemoveAllActionFromObject(ffb::Object *object)
    {
        if (m_actions.empty()) {
            return;
        }
        
        ActionVector::iterator itera = m_actions.begin();
        while (itera != m_actions.end()) {
            
            Action * action = *itera;
            
            if (action->m_actionObject == object) {
                action->release();
                m_actions.erase(itera);
            }
            else
                itera++;
        }
    }
    
    void ActionManager::Update(double dt)
    {
        if (m_actions.empty()) {
            return;
        }
        
        for(Action *action : m_actions)
        {
            if (action->m_shouldAction) {
                action->Update(dt);
            }
        }
    }
    
}








