//
//  Basic.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "BasicPtrClass.hpp"
#include <map>



namespace ffb {
    
#pragma mark - live cycle
    
    void BasicPtrClass::Clear()
    {
        m_autoRelease = false;
    }
    
    bool BasicPtrClass::Create()
    {
        return true;
    }
    
    void BasicPtrClass::Destory()
    {
        m_autoRelease = false;
    }
    
    
    
#pragma mark - memory
    
    void * BasicPtrClass::retain()
    {
        if (m_autoRelease) {
            m_autoRelease = false;
        }
        else
            m_retain++;
        
        return this;
    }
    
    void BasicPtrClass::release()
    {
        m_retain--;
        if (m_retain == 0) {
            delete this;
        }
    }
    
    void BasicPtrClass::autoRelease()
    {
        m_autoRelease = true;
    }
    
    int BasicPtrClass::getRetainCount()
    {
        return m_retain;
    }
    


}
