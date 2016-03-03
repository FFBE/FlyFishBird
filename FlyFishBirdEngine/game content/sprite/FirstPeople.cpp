//
//  FirstPeople.cpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/21.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "FirstPeople.hpp"

void FirstPeople::Clear()
{
    People::Clear();
}

void FirstPeople::Destory()
{
    People::Destory();
}

bool FirstPeople::Create()
{
    if (!People::Create()) {
        return false;
    }
    
    return true;
}

bool FirstPeople::Create(std::string fileName, float angle, float maxLength, float minLength)
{
    if (!People::Create(fileName)) {
        return false;
    }
        
    return true;
}



