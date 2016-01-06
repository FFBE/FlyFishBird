//
//  Basic.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef BasicPtrClass_hpp
#define BasicPtrClass_hpp

#include <stdio.h>
#include "Define.h"

#define     CreateClassFunctions(ClassName)\
            ClassName()                    {   Clear();    };       \
            ~ClassName()                   {   Destory();  };       \
            virtual void Clear();                                   \
            virtual bool Create();                                  \
            virtual void Destory();

#define     FFBSaveFree(ptr)            do{ if(ptr != nullptr) { ptr->release(); ptr = nullptr; } } while(0)
#define     FFBMustFree(ptr)            do{ FFBAssert(ptr != nullptr, "nullptr will be free"); ptr->release(); ptr = nullptr; } while(0);

#define     FFBSaveFreeBaseType(ptr)    do{ if(ptr != nullptr) { free(ptr); ptr = nullptr; } } while(0)
#define     FFBMustFreeBaseType(ptr)    do{ FFBAssert(ptr != nullptr, "nullptr will be free"); free(ptr); ptr = nullptr;} while(0)


#define     FFBMalloc(classname)        new classname()


namespace ffb {
    
    
    class BasicPtrClass {
        
    public:
        
        BasicPtrClass()                    {   Clear();  m_retain = 1;};
        ~BasicPtrClass()                   {   Destory();   };
        
        virtual void Clear();
        virtual bool Create();
        virtual void Destory();

        //memory
        void * retain();
        
        void release();
        
        void autoRelease();
        
        int getRetainCount();
        
        //set ptr become weak point
        void SetWeakPtr(BasicPtrClass * ptr);
        
    private:
        
        int m_retain;
        bool m_autoRelease;
    };
    
}



#endif /* Basic_hpp */
