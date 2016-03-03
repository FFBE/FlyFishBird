//
//  Action.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/23.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include "BasicPtrClass.hpp"
#include "BasicData2d.h"
#include <vector>

namespace ffb {
    
    class Object;
    
    class Action : public BasicPtrClass {
        
        friend class ActionManager;
        friend class Object;
        
    public:
        
        CreateClassFunctions(Action);
        
        void SetTag(int tag)        { m_tag = tag;              }
        int  GetTag()               { return m_tag;             }
        
        bool ShouldAction()         { return m_shouldAction;    }
        void Stop()                 { m_shouldAction = false;   }
        
        
        virtual void Start()        { m_shouldAction = true;    }
        virtual void Update(double dt) = 0;
        
    protected:
        
        bool     m_shouldAction;
        Object * m_actionObject;
        int      m_tag;
        
    };

    
    class MoveAction: public Action {
       
    public:
        
        CreateClassFunctions(MoveAction);
        
        virtual void Update(double dt);

        
    protected:
        
        Point   m_endPoint;
        float   m_time;
        Point   m_distancePerSecond;

    };
    
    
    
    class MoveLineTo : public MoveAction{
        
    public:
        
        CreateClassFunctions(MoveLineTo);
        bool Create(Point toPoint, float time);

        virtual void Start();
        
    private:
        
    };
    
    
    
    class MoveLineBy : public MoveAction{
        
    public:
        
        CreateClassFunctions(MoveLineBy);
        bool Create(Point byPoint, float time);
        
        virtual void Start();
        
    private:
                
    };
    
    
    
    class Blink : public Action{
        
    public:
        
        CreateClassFunctions(Blink);
        
        bool Create(float perTime);
        
        bool Create(float allTime, float times);
        
        virtual void Update(double dt);
        
    private:
        
        float m_perTime;
        float m_time;
        float m_allTime;
    };
    
    
    
    
    
    
    
    
    
    class ActionManager : public Singleton<ActionManager>{
        
    public:
        
        void AddAction(Action * action);
        
        void RemoveAction(Action * action);
        void RemoveAction(Object * object, int tag);
        void RemoveAllActionFromObject(Object * object);
                
        void Update(double dt);
        
    private:
        
        typedef std::vector<Action *> ActionVector;
        ActionVector m_actions;
        
    };
    
}

#endif /* Action_hpp */
