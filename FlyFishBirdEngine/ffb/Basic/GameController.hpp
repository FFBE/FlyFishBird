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

#include "Device.hpp"

namespace ffb {
    
    
    
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
        
        
        //get device
        Device * GetDevice();
        
        void LoadDefaultProgram();
        void LoadCamera();
        
        
        //root scene controller
        void SetRootScene(Scene *rootScene);
        Scene * GetCurrentScene();
        void PushScene(Scene * scene);
        void PopScene();
        
        //update
        void update(double dt);
        
        typedef std::vector<Scene *> SceneVector;
        
    private:
        
        Device * m_device;
        
        //the list of render programe
        ESProgramMap m_renderPrograms;
        
        //camera of screen
        GLESCamera m_camera;
        
        SceneVector m_sceneVector;
        
        float   m_glVersion;
                
    };
    
    
    static short defaultProgram = 0;
}



#endif /* FFBGLESController_hpp */
