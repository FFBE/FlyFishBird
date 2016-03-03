//
//  Macro.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/19.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Macro_hpp
#define Macro_hpp




#ifdef __APPLE__
#define FFBDEBUG        DEBUG
#else
#define FFBDEBUG        1
#endif




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



#define function0st(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define function1st(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define function2st(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)



#define CreateSimpleClass( Class , SuperClass)\
void Class::Clear()\
{\
    SuperClass::Clear();\
}\
void Class::Destory()\
{\
    SuperClass::Destory();\
}\
bool Class::Create()\
{\
    if (!SuperClass::Create()) {\
        return false;\
    }\
    return true;\
}


#endif /* Macro_hpp */
