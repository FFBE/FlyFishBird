//
//  Renderer.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/15.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Renderer.hpp"
#include "GameController.hpp"


namespace ffb {
#pragma mark - Transform
    
    
    void Renderer::Clear()
    {
        m_rotate = 0;
        m_scale = PointMake(1, 1);
        m_point = PointMake(0, 0);
        BasicPtrClass::Clear();
    }
    
    void Renderer::Destory()
    {   
        BasicPtrClass::Destory();
    }

    
    bool Renderer::Create()
    {
        return Create(defaultProgram);
    }
    
    bool Renderer::Create(short key)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        m_glprogram = GameController::GetSingleton().GetProgramWithKey(key);
        Create(m_glprogram);
        
        return true;
    }
    
    bool Renderer::Create(ffb::GLESProgram *programe)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_glprogram = programe;
        
        return true;
    }

    
    void Renderer::SetPosition(Point point)
    {
        m_point = point;
    }
    
    void Renderer::SetPosition(float x, float y)
    {
        m_point.x = x;
        m_point.y = y;
    }
    
    Point Renderer::GetPosition()
    {
        return m_point;
    }
    
    void Renderer::SetScale(float scale)
    {
        m_scale.x = scale;
        m_scale.y = scale;
    }
    
    void Renderer::SetScale(float scaleX, float scaleY)
    {
        m_scale.x = scaleX;
        m_scale.y = scaleY;
    }
    
    void Renderer::SetScale(Point scale)
    {
        m_scale = scale;
    }
    
    Point Renderer::GetScale()
    {
        return m_scale;
    }
    
    void Renderer::SetRotate(float rotate)
    {
        m_rotate = rotate;
    }
    
    float Renderer::GetRotate()
    {
        return m_rotate;
    }

    void Renderer::Render()
    {
        Matrix camera = GameController::GetSingletonPtr()->GetCameraMatrix();
        
        float scale = Device::GetSingleton().GetScreenScale();
        MatrixLoadIdentity(&m_mvpMatrix);
        Translate(&m_mvpMatrix, m_point.x*scale, m_point.y*scale, 0);
        Rotate(&m_mvpMatrix, m_rotate, 0, 0, 1);
        Scale(&m_mvpMatrix, m_scale.x, m_scale.y, 1);
        MatrixMultiply(&m_mvpMatrix, &m_mvpMatrix, &camera);
    }
}