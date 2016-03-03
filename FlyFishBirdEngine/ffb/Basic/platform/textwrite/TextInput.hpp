//
//  TextInput.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef TextInput_hpp
#define TextInput_hpp

#include <stdio.h>
#include "BasicPtrClass.hpp"
#include "BasicData2d.h"

namespace ffb {
    
    class TextInput : public BasicPtrClass {
        
        
    public:
        
        void CreateTextInputInRect(Point point, Size size, int tag);
        void DestoryTexInputByTag(int tag);
        
        void SetTextInputHiddenByTag(int tag, bool hidden);
        
        std::string GetTextByTag(int tag);
        void SetTextByTag(int tag, std::string text);
        
    private:
        
    };
    
}





#endif /* TextInput_hpp */
