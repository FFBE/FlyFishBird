//
//  People.hpp
//  FlyFishBirdEngine
//
//  Created by apple on 16/2/20.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef People_hpp
#define People_hpp

#include <stdio.h>
#include "Sprite.hpp"
#include "DrawObject.hpp"

class People:public ffb::Sprite  {
    
    
public:
    
    struct Direction
    {
        float right;
        float up;
    };
    
    CreateClassFunctions(People);
    bool Create(std::string fileName);
    
    static People * Create(int number);
    
    void SetFirstAngle(double angle);
    
    float GetRighSpeed();
    
    void StartSwing(float ropeLength, ffb::Point centerPoint);
    
    virtual void Update(double dt);
    
    void SetRopeAppear(bool appear);
    bool GetRopeAppear();
    
    void DrawRopeToPoint(ffb::Point point);
    
private:
    
    bool        m_isSwing;
    
    //swing
    double TransformAngle(double angle)
    {
        
        while (angle < -PI/2) {
            
            FFBAssert(angle != PI, "");
            angle += PI;
        }
        while (angle > PI/2) {
            
            FFBAssert(angle != PI, "");
            angle -= PI;
        }
        
        return angle;
    }
    
    enum SportType
    {
        SportTypeLeftToRight = 1,
        SportTypeRightToLeft,
    };
    
    SportType m_sprotType;
    //    Direction m_acceleration;
    
    ffb::DrawObject *m_drawObject;
    
    ffb::Point m_centerPoint;
    
    float m_ropeLength;       //绳长
    double m_angle;
    double m_angleSpeed;
    
    bool m_isRopeAppear;
    ffb::Point m_ropePoint;
    
    //fly
    Direction m_speed;

};

#endif /* People_hpp */
