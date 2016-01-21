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
#include "Macro.h"




namespace ffb {
    
    /*
     *  指针基类
     */
    class BasicPtrClass {
        
    public:
        
        BasicPtrClass()                             {   Clear();  m_retain = 1;};
        virtual ~BasicPtrClass()                    {   Destory();   };
        
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
        
    };
    
}



#endif /* Basic_hpp */
