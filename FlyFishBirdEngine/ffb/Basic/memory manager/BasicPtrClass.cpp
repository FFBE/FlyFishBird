//
//  Basic.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "BasicPtrClass.hpp"
#include "AutoReleasePool.hpp"
#include <map>


namespace ffb {
    
#pragma mark - live cycle
    
    void BasicPtrClass::Clear()
    {
    }
    
    void BasicPtrClass::Destory()
    {
    }
    
    bool BasicPtrClass::Create()
    {
        return true;
    }
    
   
    
    
    
#pragma mark - memory
    
    void  BasicPtrClass::retain()
    {
        FFBAssert(m_retain, "retain can not be 0");
        m_retain++;
    }
    
    void BasicPtrClass::release()
    {
        m_retain--;
        if (m_retain == 0) {
            Destory();
            delete this;
        }
    }
    
    void BasicPtrClass::autoRelease()
    {
        PoolManager::GetSingletonPtr()->GetMainPool()->Add(this);
    }
    
    int BasicPtrClass::getRetainCount()
    {
        return m_retain;
    }
    


}
