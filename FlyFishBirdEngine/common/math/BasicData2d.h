//
//  FFBBasicData2d.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef FFBBasicData2d_hpp
#define FFBBasicData2d_hpp

#include <stdio.h>
#include <string>

namespace ffb {
    
    /*Point*/
    
    typedef struct
    {
        float x, y;
    }Point;
    
    typedef Point *  PointPtr;
    
    static inline Point PointMake(float x, float y)
    {
        return (Point){x, y};
    }
    
    static inline bool PointIsEqualToPoint(Point point1, Point point2)
    {
        return (point1.x == point2.x) && (point1.y == point2.y);
    }
    
    /*Size*/
    
    typedef struct
    {
        float width, height;
    }Size;
    
    static inline Size SizeMake(float width, float height)
    {
        return (Size){width, height};
    }
    
    static inline bool SizeIsEuqlToSize(Size size1, Size size2)
    {
        return (size1.width == size2.width) && (size1.height == size2.height);
    }
    
    
    
    
    
    typedef struct
    {
        float r, g, b, a;
    }Color;
    
    static inline Color ColorMake(float r, float g, float b, float a)
    {
        return (Color){r, g, b, a};
    }
    
    
    static inline bool ColorIsEuqlToColor(Color c1, Color c2)
    {
        return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
    }
    
}




#endif /* FFBBasicData2d_hpp */
