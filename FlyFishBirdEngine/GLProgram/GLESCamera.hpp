//
//  GLESCamera.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef GLESCamera_hpp
#define GLESCamera_hpp

#include <stdio.h>
#include "BasicPtrClass.hpp"
#include "SimpleMath.h"

namespace ffb {
    
    
    class GLESCamera:public BasicPtrClass {
        
    public:
    
        
        CreateClassFunctions(GLESCamera);

        
        Matrix GetCameraMatrix();
        
        //create camera matrix
        void CameraFrustum ( float left, float right, float bottom, float top, float nearZ, float farZ );
        void CameraPerspective ( float fovy, float aspect, float nearZ, float farZ );
        void CameraOrtho ( float left, float right, float bottom, float top, float nearZ, float farZ );
        void CameraMatrixLookAt ( float posX,    float posY,    float posZ,
                                 float lookAtX, float lookAtY, float lookAtZ,
                                 float upX,     float upY,     float upZ );
        
        
        //translation camera matrix
        void CameraMove ( float x, float y , float z );
        void CameraScale ( float x, float y, float z );
        void CameraRoate ( float angle, float x, float y, float z );
        
        
    private:
        
        Matrix m_cameraMatrix;
    };
    
}

#endif /* GLESCamera_hpp */
