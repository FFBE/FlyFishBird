//
//  Scroll.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/25.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Scroll.hpp"
#include "TimeSchedule.hpp"

namespace ffb {
    
    
    void Scroll::Clear()
    {
        Object::Clear();
        m_cutOffIfOut = false;
        m_beginFromTop = true;
        m_subObjectCanTouch = false;
        m_canScroll =false;
        m_lastMovePoint = PointMake(0, 0);
        m_scrollSpeed = 0;
        m_scrollOffSet = PointMake(0, 0);
        m_lastTouchTime = 0;
    }
    
    void Scroll::Destory()
    {
        Object::Destory();
    }
    
    bool Scroll::Create()
    {
        if (!Object::Create()) {
            return false;
        }
        
        return true;
    }
    
    bool Scroll::Create(Size size, Size contentOfSize)
    {
        if (!Object::Create()) {
            return false;
        }
        
        m_size = size;
        m_contentSize = contentOfSize;
        
        return true;
    }
    
    void Scroll::AddObjectToScroll(ffb::TouchObject *object)
    {
        if (m_beginFromTop) {
            object -> SetPosition(object->GetPosition().x, -object->GetPosition().y);
        }
        AddObject(object);
    }
    
    void Scroll::AddObjectsToScroll(std::vector<TouchObject *> objectList)
    {
        size_t length = objectList.size();
        Object * object;
        for (size_t i = 0; i<length; i++) {
            object = objectList[i];
            if (m_beginFromTop) {
                object -> SetPosition(object->GetPosition().x, -object->GetPosition().y);
            }
            AddObject(object);
        }
    }
    
    void Scroll::SetCutOffIfOut(bool cutOffIfOut)
    {
        m_cutOffIfOut = cutOffIfOut;
    }
    
    bool Scroll::GetCutOffIfOut()
    {
        return m_cutOffIfOut;
    }
    
    void Scroll::SetBeginFromTop(bool beginFormTop)
    {
        m_beginFromTop = beginFormTop;
    }
    
    bool Scroll::GetBeginFromTop()
    {
        return m_beginFromTop;
    }
    
    void Scroll::SubObjectCannotTouch()
    {
        m_subObjectCanTouch = false;
    }
    
    Point Scroll::GetScrollOfSet()
    {
        if (m_beginFromTop) {
            return m_scrollOffSet;
        }
        return PointMake(m_scrollOffSet.x, -m_scrollOffSet.y);
    }
    
    void Scroll::SetScrollOfSet(Point scrollOfSet)
    {
        SetScrollOfSet(scrollOfSet, true);
    }
    
    void Scroll::SetScrollOfSet(Point scrollOfSet, bool animation)
    {
        SetScrollOfSet(scrollOfSet, animation, 1.0);
    }
    
    void Scroll::SetScrollOfSet(Point scrollOfSet, bool animation, float time)
    {
        if (!animation) {
            if (m_beginFromTop) {
                m_scrollOffSet = scrollOfSet;
            }
            m_scrollOffSet = PointMake(scrollOfSet.x, -scrollOfSet.y);
            return;
        }
        m_scrollSpeed = scrollOfSet.y/time;
        m_scrollDeceleration = 0;
    }
    
    void Scroll::SetSize(Size size)
    {
        m_size = size;
    }
    
    Size Scroll::GetSize()
    {
        return m_size;
    }
    
    
    bool Scroll::TouchShouldBegin(Touch * touch)
    {
        Point touchPoint = touch->ConverTouchPointToObject(this);
        
        if ( (0 < touchPoint.x && touchPoint.x < m_size.width * m_renderer->GetScale().x &&
              touchPoint.y < 0 && touchPoint.y > -m_size.height * m_renderer->GetScale().y && m_beginFromTop) ||
            (0 < touchPoint.x && touchPoint.x < m_size.width * m_renderer->GetScale().x &&
             0<touchPoint.y && touchPoint.y < m_size.height * m_renderer->GetScale().y  && !m_beginFromTop) ) {
            
            m_subObjectCanTouch = true;
            m_canScroll = false;
            TimeSchedule::GetSingletonPtr()->AddSchedule(function0st(Scroll::SubObjectCannotTouch, this), 0.2);
            
            m_lastMovePoint = touchPoint;
            
            return true;
        }
        
        return false;
    }
    
    void Scroll::TouchMoved(Touch * touch)
    {
        m_subObjectCanTouch = false;

        if (m_contentSize.height < m_size.height) {
            return;
        }
        
        Point touchPoint = touch->ConverTouchPointToObject(this);
        
        float distancey = touchPoint.y - m_lastMovePoint.y;
        m_scrollOffSet = PointMake(m_scrollOffSet.x, distancey + m_scrollOffSet.y);
        
        m_scrollSpeed = distancey/(touch->GetTouchTimestamp()-m_lastTouchTime)/10;
        m_scrollDeceleration = 1;
        m_lastMovePoint = touchPoint;
        m_lastTouchTime = touch->GetTouchTimestamp();
    }
    
    void Scroll::TouchEnd(Touch * touch)
    {
        if (m_subObjectCanTouch == true) {
            m_canScroll = false;
            ObjectList::iterator itera = m_objectList.begin();
            Object * object;
            for (; itera != m_objectList.end(); ++itera) {
                object = *itera;
                if (object->TouchShouldBegin(touch)) {
                    TouchObject * touchObject = static_cast<TouchObject *>(object);
                    touchObject -> TouchEnd(touch);
                }
            }
        }
        else
        {
            m_canScroll = true;
        }
    }
    
    void Scroll::Update(double dt)
    {
        if ((m_scrollOffSet.y<0 && m_beginFromTop) || (m_scrollOffSet.y>0 && !m_beginFromTop)) {
            m_scrollOffSet = PointMake(0, 0);
            m_canScroll = false;
            return;
        }
        else if (abs(m_scrollOffSet.y)+m_size.height > m_contentSize.height) {
            m_scrollOffSet = PointMake(m_scrollOffSet.x, m_contentSize.height-m_size.height * (m_beginFromTop?1:-1));
            m_canScroll = false;
            return;
        }
        
        if (!m_canScroll) {
            return;
        }
        
        float distancey, scrollSpeed;
        if (m_scrollSpeed > 0) {
            scrollSpeed = m_scrollSpeed-m_scrollDeceleration;
        }
        else
            scrollSpeed = m_scrollSpeed+m_scrollDeceleration;

        if ((scrollSpeed < 0 && m_scrollSpeed > 0) || (scrollSpeed > 0 && m_scrollSpeed < 0)) {
            distancey = m_scrollSpeed*dt*0.5;
            scrollSpeed = 0;
            m_canScroll = false;
        }
        else
        {
            distancey = (m_scrollSpeed + scrollSpeed)*0.5*dt;
            m_scrollSpeed = scrollSpeed;
        }
        
        m_scrollSpeed = scrollSpeed;
        m_scrollOffSet = PointMake(m_scrollOffSet.x, m_scrollOffSet.y+distancey);
        m_scrollDeceleration += m_scrollDeceleration/5;
    }
    
    void Scroll::Render()
    {
        if (m_objectList.empty()) {
            return;
        }
        
        float supMeshRotate = 0;
        Point supMeshPostion = PointMake(0, 0);
        Point supMeshScale = PointMake(1, 1);
        
        if (m_supObject != nullptr) {
            supMeshPostion = PointMake(m_supObject->GetRenderer()->GetPosition().x, m_supObject->GetRenderer()->GetPosition().y);
            supMeshScale = PointMake(m_supObject->GetRenderer()->GetScale().x, m_supObject->GetRenderer()->GetScale().y);
            supMeshRotate = m_supObject->GetRenderer()->GetRotate();
        }
        
        m_renderer->SetPosition(supMeshPostion.x+m_position.x+m_scrollOffSet.x, supMeshPostion.y+m_position.y+m_scrollOffSet.y);
        m_renderer->SetScale(supMeshScale.x*m_scale.x, supMeshScale.y*m_scale.y);
        m_renderer->SetRotate(supMeshRotate+m_rotate);
        
        ObjectList::iterator itera;
        Object * object;
        
        for (itera=m_objectList.begin(); itera != m_objectList.end(); itera++) {
            object = (Object *)(*itera);
            object->Render();
        }
        
        m_renderer->SetPosition(supMeshPostion.x+m_position.x+m_scrollOffSet.x, supMeshPostion.y+m_position.y);

    }
    
}
