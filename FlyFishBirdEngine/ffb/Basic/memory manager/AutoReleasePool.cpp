//
//  PtrClassManager.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/15.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "AutoReleasePool.hpp"

namespace ffb {

    
    AutoReleasePool::AutoReleasePool()
    {
        m_managerVector.reserve(100);
        PoolManager::GetSingleton().PushPool(this);
    }
    
    void AutoReleasePool::Add(ffb::BasicPtrClass *ptr)
    {
        m_managerVector.push_back(ptr);
    }
    
    void AutoReleasePool::Clear()
    {
        for (auto ptr : m_managerVector)
        {
            ptr->release();
        }
        m_managerVector.clear();
    }
    
    void AutoReleasePool::Destory()
    {
        Clear();
        PoolManager::GetSingleton().PopPool();
        delete this;
    }
    
    
    
    
    
    PoolManager::PoolManager()
    {
        m_poolManager.reserve(10);
        m_mainPool = new AutoReleasePool();
    }
    
    void PoolManager::PushPool(AutoReleasePool *pool)
    {
        m_poolManager.push_back(pool);
    }
    
    void PoolManager::PopPool()
    {
        AutoReleasePool * pool = m_poolManager.back();
        m_poolManager.pop_back();
        delete pool;
    }
    
    AutoReleasePool * PoolManager::GetTopPool()
    {
        return m_poolManager.back();
    }
    
    AutoReleasePool * PoolManager::GetMainPool()
    {
        return m_mainPool;
    }
    
}
