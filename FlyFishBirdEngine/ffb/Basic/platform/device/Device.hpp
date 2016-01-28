//
//  Device.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/22.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Device_hpp
#define Device_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include "BasicData2d.h"

#include "GLESCamera.hpp"


namespace ffb {
    class Device:public Singleton<Device> {
        
        
        
    public:
        
        //set screen size
        void SetScreenScale(float scale);
        float GetScreenScale();
        
        void SetScreenSize(float width, float height);
        float GetScreenWidth();
        float GetScreenHeight();
        Size GetScreenSize();
        
        
    private:
        
        Size m_screenSize;
        float   m_scale;
        
        
        //camera of screen
        GLESCamera m_camera;
    };
}



#endif /* Device_hpp */
