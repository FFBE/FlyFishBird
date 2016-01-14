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
        
        void SetString(std::string text);
        std::string GetString();
        
    private:
        
        Texture2D * m_Texture;

    };
}


#endif /* Label_hpp */