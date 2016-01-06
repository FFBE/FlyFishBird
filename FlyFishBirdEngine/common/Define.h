//
//  FFBDefine.h
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/3.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Define_h
#define Define_h


#include "cassert"


#define FFBAssertWhenExpn(expn)         typedef char __C_ASSERT__[(expn)?1:-1]
#define FFBAssert(a, msg)       assert( a && msg)


#define UnsignedIntMax                          4394967295

#endif /* FFBDefine_h */
