//
//  PtrClassManager.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/15.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef PtrClassManager_hpp
#define PtrClassManager_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "Singleton.hpp"
#include "BasicPtrClass.hpp"

namespace ffb {
    
    
    
    class AutoReleasePool
    {
    private:
        
        std::vector<BasicPtrClass *> m_managerVector;
        
        
    public:
        
        AutoReleasePool();
        ~AutoReleasePool() {};
        
        void Add(BasicPtrClass * ptr);
        
        void Clear();
        
        void Destory();
    };
    
    
    class PoolManager:public Singleton<PoolManager> {
        
        // a stack pool vector
        std::vector<AutoReleasePool *> m_poolManager;
        AutoReleasePool * m_mainPool;
        
    public:
        
        PoolManager();
        ~PoolManager();
    
        void PushPool(AutoReleasePool * pool);
        
        void PopPool();
        
        AutoReleasePool * GetTopPool();

        AutoReleasePool * GetMainPool();
    };
    
}


#endif /* PtrClassManager_hpp */
