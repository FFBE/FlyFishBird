//
//  FFBGLESController.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef FFBGLESController_hpp
#define FFBGLESController_hpp

#include <stdio.h>
#include <map>
#include <stack>

#include "Singleton.hpp"
#include "GLESProgram.hpp"
#include "GLESCamera.hpp"
#include "Scene.hpp"

namespace ffb {
    
    
#define InsertProgramMapType(key, value) std::map< short, GLESProgram *>::value_type(key, value)
    
    typedef std::map < short, GLESProgram * > ESProgramMap;
    
    class GameController:public Singleton<GameController> {

    public:
        
        GameController();
        ~GameController();
        
        void SetGLVersion(float);
        float GetGLVersion();
        
        const Matrix GetCameraMatrix();
        
        //gl es programe manager
        const ESProgramMap GetProgramMap();

        void AddProgram(GLESProgram*program, short key);
        GLESProgram * GetProgramWithKey(short key);
        void RemoveProgramWithKey(short key);
        
        
        //set screen size
        void SetScreenScale(float scale);
        float GetScreenScale();
        
        void SetScreenSize(float width, float height);
        float GetScreenWidth();
        float GetScreenHeight();
        Size GetScreenSize();
        
        
        //root scene controller
        void SetRootScene(Scene *rootScene);
        Scene * GetRootScene();
        
        //update
        void update(double dt);
        //render
        void render();
    private:
        
        //the list of render programe
        ESProgramMap m_renderPrograms;
        
        //camera of screen
        GLESCamera m_camera;
        
        Size m_screenSize;
        float   m_scale;
        
        Scene * m_rootScene;
        
        float   m_glVersion;
        
    };
    
    
    static short defaultProgram = 0;
}



#endif /* FFBGLESController_hpp */
