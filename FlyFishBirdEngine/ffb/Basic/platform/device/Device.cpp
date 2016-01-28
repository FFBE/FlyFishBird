//
//  Device.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/22.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "Device.hpp"
#include "GameController.hpp"

#pragma mark - GL Screen Manager

namespace ffb {
    
    
    void Device::SetScreenSize(float width, float height)
    {
        m_screenSize.width = width;
        m_screenSize.height = height;
        
        GameController::GetSingletonPtr()->LoadDefaultProgram();
        GameController::GetSingletonPtr()->LoadCamera();
    }
    
    void Device::SetScreenScale(float scale)
    {
        m_scale = scale;
    }
    
    float Device::GetScreenScale()
    {
        return m_scale;
    }
    
    float Device::GetScreenWidth()
    {
        return m_screenSize.width;
    }
    
    float Device::GetScreenHeight()
    {
        return m_screenSize.height;
    }
    
    Size Device::GetScreenSize()
    {
        return m_screenSize;
    }
    
    
}
