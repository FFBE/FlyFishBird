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
        
        bool Create(const std::string &text);
        bool Create(const std::string &text, float fontSize);
        bool Create(const std::string &fontName,const std::string &text, float fontSize);
        
        void SetText(const std::string &text);
        std::string GetText();
        
        void SetTextColor(float r, float g, float b, float a);
        void SetTextColor(Color color);
        Color GetTextColor();
        
        Size GetSize();
        
    protected:
        
        Size        m_size;
        
    private:
        
        std::string m_text;
        std::string m_fontName;
        float       m_fontSize;
        Color       m_textColor;
        
        Texture2D * m_Texture;

    };
}


#endif /* Label_hpp */
