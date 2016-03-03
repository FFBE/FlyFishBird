//
//  Scene.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/4.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "BasicPtrClass.hpp"
#include "Object.hpp"

namespace ffb {
    
    class Scene: public BasicPtrClass {
        
    public:
        
        
        typedef std::function<void (Scene *)> SceneFunction;
        
        
        CreateClassFunctions(Scene);
        bool Create(Object * rootObject);
        
        // update and render object
        virtual void Render();
        virtual void Update(double dt);
        
        //rootObject
        Object * GetRootObject();
        
        //touchObject
        void CheckTouchObject(Touch * touch);
        Object * GetTouchObject();
        void ResetTouchObject();
        
        //color
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
        Color GetColor();
        
    protected:
        
        Object * m_rootObject;
        
        Object * m_touchObject;
        
    };
    
    
    
    
    
#pragma mark - TransformScene
    
    class TransformScene : public ffb::Scene{
      
    public:
    
        CreateClassFunctions(TransformScene);
        
        bool Create(float transformTime);
        
        virtual void Render();
        
        void SetSubScene(Scene * subScene);
        
        virtual void SceneStartPush();
        virtual double PushAction();    //return a time about action
        virtual void SceneEndPush();
        
        virtual void SceneStartPop();
        virtual double PopAction();     //return a time about action
        virtual void SceneEndPop();
        
    protected:
        
        float       m_transformTime;
        
    private:
        
        bool        m_shouldRenderSubScene;
        Scene       * m_subScene;
        
    };
    
    
    
    
    
    class  RightToLeftScene : public ffb::TransformScene {
        
        
    public:
        
        CreateClassFunctions(RightToLeftScene);
        
        virtual double PushAction();
        virtual double PopAction();
        
    private:
        
        
        
    };
    
    
    

}

#endif /* Scene_hpp */
