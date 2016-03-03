//
//  People.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "People.hpp"
#include "FirstPeople.hpp"
#include "Device.hpp"
#include <math.h>

#define G           100          //重力加速度

using namespace ffb;

void People::Clear()
{
    Sprite::Clear();
    
    m_drawObject = FFBMalloc(DrawObject);
    m_speed.right = 0;
    m_speed.up = 0;
    m_centerPoint = PointMake(Device::GetSingletonPtr()->GetScreenSize().width/2, Device::GetSingletonPtr()->GetScreenSize().height);
    m_ropeLength = 200;
    m_angleSpeed= 0;
    m_sprotType = SportTypeRightToLeft;
    m_isSwing = false;
    m_isRopeAppear = false;
}

void People::Destory()
{
    FFBSaveFree(m_drawObject);
    Sprite::Destory();
}

bool People::Create()
{
    if (!Sprite::Create()) {
        return false;
    }
    
    return true;
}

bool People::Create(std::string fileName)
{
    if (!Sprite::Create(fileName)) {
        return false;
    }
    
    m_drawObject->Create();
    AddObject(m_drawObject);
    
    return true;
}

float People::GetRighSpeed()
{
    return m_speed.right;
}

People * People::Create(int number)
{
    FirstPeople * first = FFBMalloc(FirstPeople);
    first->Create("people1", 45, 180, 90);
    return first;
}

void People::SetFirstAngle(double angle)
{
    while (angle < -PI/2) {
        
        FFBAssert(angle != PI, "");
        angle += PI;
    }
    while (angle > PI/2) {
        
        FFBAssert(angle != PI, "");
        angle -= PI;
    }
    m_angle = angle;
}

void People::StartSwing(float ropeLength, ffb::Point centerPoint)
{
    m_ropeLength = ropeLength;
    m_centerPoint = centerPoint;
    m_isSwing = true;
}

void People::SetRopeAppear(bool appear)
{
    m_isRopeAppear = appear;
}

bool People::GetRopeAppear()
{
    return m_isRopeAppear;
}

void People::Update(double dt)
{
    if (!m_isSwing) {
        
        Size screenSize = Device::GetSingletonPtr()->GetScreenSize();
        
        float b = 0;   //x
        float a = 0;   //y
        float v = 0;
        
        float x, y;
        
        if (m_speed.right*m_speed.right + m_speed.up * m_speed.up == 0) {
            
            v = dt * G;
            float h = v * v  / 2 / G;
            
            a = screenSize.height+h-m_position.y;
            
            if (m_position.x < m_centerPoint.x) {
                b = sqrt(m_ropeLength*m_ropeLength-a*a);
            }
            else
                b = -sqrt(m_ropeLength*m_ropeLength-a*a);
            
            double angle = TransformAngle( atan(b/a) );
            m_angleSpeed = (angle-m_angle)/dt;
            m_angle = angle;
        }
        else
        {
            double distanceAngle = m_angleSpeed*dt;
            double angle = 0;
            
            angle = m_angle+distanceAngle;
            
            b = m_ropeLength * sin(angle);
            a = m_ropeLength * cos(angle);
            
            float h = m_position.y + a - screenSize.height;
            
            double doubleV = m_speed.up*m_speed.up+m_speed.right*m_speed.right + 2*G*h;
            
            if (doubleV < 0) {
                m_angleSpeed = 0;
                v = 0;
            }
            else
                v = sqrt(doubleV);
            
            if (m_angleSpeed > 0) {
                m_angleSpeed = v/m_ropeLength*2;
            }
            else
                m_angleSpeed = -v/m_ropeLength*2;
            
            m_angle = angle;
        }
        
        m_speed.up = v * sin(m_angle);
        m_speed.right = v * cos(m_angle);
        
        x = m_centerPoint.x - m_ropeLength*sin(m_angle);
        y = m_centerPoint.y - m_ropeLength*cos(m_angle);
        
        m_position = PointMake( x, y);
    }
    else
    {
        m_position = PointMake(m_position.x+m_speed.right*dt, m_position.y+m_speed.up*dt);
        
        if (m_isRopeAppear == false) {
            return;
        }
        
        float distanceY = m_centerPoint.y - m_position.y;
        float distancex = m_centerPoint.x - m_position.x;
        
        if (distancex*distancex + distanceY * distanceY <= m_ropeLength * m_ropeLength) {
            m_isSwing = true;
        }
    }
}
















