//
//  CommonTeplate.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <stdio.h>

#include "Macro.h"


namespace ffb {
    
    
    
    template <typename T>
    class Singleton {
        
    private:
        
        static T* ms_Singleton;
        
    public:
        Singleton()
        {
            FFBAssert(!ms_Singleton, "singleton must be nullptr before create");
            int offSet = (long)(T*)1-(long)(Singleton<T>*)(T*)1;//子类相对父类指针的偏移量
            ms_Singleton = (T*)((long)this+offSet);
        }
        
        ~Singleton()
        {
            FFBAssert(ms_Singleton, "singleton is nullptr before destory"); ms_Singleton = 0;
        }
        
        static T& GetSingleton()
        {
            if (ms_Singleton == nullptr) {
                ms_Singleton = new T();
                FFBAssert(ms_Singleton, "init singleton failed");
            }
            return *ms_Singleton;
        }
        
        static T* GetSingletonPtr()
        {
            if (ms_Singleton == nullptr) {
                ms_Singleton = new T();
                FFBAssert(ms_Singleton, "init singleton failed");
            }
            FFBAssert(ms_Singleton, "singleton is nullptr");
            return ms_Singleton;
        }
    };
    
    
    
    template <typename T> T* Singleton <T>::ms_Singleton = 0;
}


#endif /* CommonTeplate_hpp */
