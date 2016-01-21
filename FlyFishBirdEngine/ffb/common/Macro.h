//
//  Macro.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/19.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Macro_hpp
#define Macro_hpp


#define UnsignedIntMax                          4394967295


#include "cassert"


#define FFBAssertWhenExpn(expn)         typedef char __C_ASSERT__[(expn)?1:-1]
#define FFBAssert(a, msg)       assert( a && msg)







#define     CreateClassFunctions(ClassName)\
ClassName()                    {   Clear();    };       \
virtual void Clear();                                   \
virtual bool Create();                                  \
virtual void Destory();

#define     FFBSaveFree(ptr)            do{ if(ptr != nullptr) { ptr->release(); ptr = nullptr; } } while(0)

#define     FFBSaveFreeBaseType(ptr)    do{ if(ptr != nullptr) { free(ptr); ptr = nullptr; } } while(0)


#define     FFBMalloc(classname)        new classname()













#endif /* Macro_hpp */
