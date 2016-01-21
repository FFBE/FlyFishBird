//
//  GLESBaseProgram.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/17.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef GLESBaseProgram_hpp
#define GLESBaseProgram_hpp

#include <stdio.h>
#include <OpenGLES/gltypes.h>
#include <iostream>
#include <OpenGLES/ES3/gl.h>
#include "BasicPtrClass.hpp"

#include "ReadFile.h"

namespace ffb {
    
    
    class GLESBaseProgram:public BasicPtrClass {
        
    public:
        
        CreateClassFunctions(GLESBaseProgram);
        
        bool Create(std::string vertexShaderFile, std::string fragmentShaderFile);
        bool Create(const char * vertexShader, const char * fragmentShader);
        
        //create gl programe
        GLuint LoadGLESProgram(const char * vertecShader, const char * fragmentShader);
        
        GLuint GetProgram();
        
        //load the vertex/fragment shader.
        //you can fix the function to platform you want
        GLuint LoadShader(GLuint type, const char * shaderStr);
        
        //shut down gl programe
        void ShutDownGL();
        
        
        /*shader set*/
        virtual void ResetShader() = 0;
        
    protected:
        
        
        
        
        
        
        // the handle of gl programe
        GLuint          m_programObject;
        
        float         m_glVersion;
    };
    
}

#endif /* GLESBaseProgram_hpp */
