//
//  ClickLabel.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef ClickLabel_hpp
#define ClickLabel_hpp

#include <stdio.h>
#include "Label.hpp"
#include "TouchObject.hpp"

namespace ffb {
    
    class TouchLabel:public TouchObject{
        
        
        
    public:
        
        CreateClassFunctions(TouchLabel);
        
        bool Create(std::string text);
        bool Create(std::string text, float size);
        bool Create(std::string text, float size, std::string fontName);
        
        void SetTouchScale(float touchScale);
        float GetTouchScale();
        
        void SetTouchColor(Color touchColor);
        Color GetTouchColor();
        
        void SetTouchText(std::string text);
        std::string GetTouchText();
        
        TouchEventFuncation;
        
        Label * GetLabel();
        
    private:
        
        Label               * m_label;
        
        float               m_touchScale;
        Color               m_touchColor;
        std::string         m_touchText;
        
    };
    
}

#endif /* ClickLabel_hpp */
