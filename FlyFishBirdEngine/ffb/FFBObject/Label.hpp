//
//  Label.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/11.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include <stdio.h>
#include "Object.hpp"
#include "Texture2D.hpp"


namespace ffb {
    class Label:public Object {
        
        
        
    public:
        
        CreateClassFunctions(Label);
        
        bool Create(std::string fontName, std::string text, float fontSize);
        
        void SetText(std::string text);
        std::string GetText();
        
        void SetColor(float r, float g, float b);
        Color GetColor();
    private:
        
        std::string m_text;
        std::string m_fontName;
        float       m_fontSize;
        
        Texture2D * m_Texture;

    };
}


#endif /* Label_hpp */
