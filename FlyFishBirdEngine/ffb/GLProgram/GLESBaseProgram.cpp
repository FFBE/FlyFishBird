//
//  GLESBaseProgram.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/17.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GLESBaseProgram.hpp"
#include <OpenGLES/ES3/glext.h>
#include "GameController.hpp"

namespace ffb {
    
    
    static const char * platformES3VertexShaderMacro    =   "#version 300 es                            \n";
    
    static const char * platformES3FragmentShaderMacro  =   "#version 300 es                            \n";
    
    static const char * platformES2VertexShaderMacro    =   "#ifndef ES2 \n#define ES2                  \n"
                                                            "#endif \n#define in attribute              \n"
                                                            "#define out varying                        \n"
                                                            "#define layout(a)                          \n";
    
    static const char * platformES2FragmentShaderMacro  =   "#ifndef ES2                                \n"
                                                            "#define ES2                                \n"
                                                            "#endif                                     \n"
                                                            "#define in varying                         \n"
                                                            "#define layout(a)                          \n"
                                                            "#define texture texture2D                  \n";


    
    void GLESBaseProgram::Clear()
    {
        m_programObject = 0;
        
        BasicPtrClass::Clear();
    }
    
    bool GLESBaseProgram::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_glVersion = GameController::GetSingletonPtr()->GetGLVersion();
        
        return true;
    }
    
    bool GLESBaseProgram::Create(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_programObject = LoadGLESProgram(ReadFile(vertexShaderFile.c_str()), ReadFile(fragmentShaderFile.c_str()));
        
        if (m_programObject == 0) {
            printf("error: failed to create programe\n");
            return false;
        }
        
        return true;
    }

    bool GLESBaseProgram::Create(const char *vertecShader, const char *fragmentShader)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_programObject = LoadGLESProgram(vertecShader, vertecShader);
        return true;
    }
    
    void GLESBaseProgram::Destory()
    {
        BasicPtrClass::Destory();
    }
    
#pragma mark - render
    
    
    void GLESBaseProgram::ShutDownGL()
    {
        glDeleteProgram(m_programObject);
    }
    
    
    GLuint GLESBaseProgram::GetProgram()
    {
        return m_programObject;
    }
    
    
#pragma mark - gl prgrame
    
    GLuint GLESBaseProgram::LoadGLESProgram(const char * vertexShaderStr, const char * fragmentShaderStr)
    {
        m_glVersion = GameController::GetSingletonPtr()->GetGLVersion();
        std::string vertexShaderData = vertexShaderStr, fragmentShaderData = fragmentShaderStr;

        if (GameController::GetSingleton().GetGLVersion()>=3.0) {
            vertexShaderData = platformES3VertexShaderMacro + vertexShaderData;
            fragmentShaderData = platformES3FragmentShaderMacro + fragmentShaderData;
        }
        else
        {
            vertexShaderData = platformES2VertexShaderMacro + vertexShaderData;
            fragmentShaderData = platformES2FragmentShaderMacro + fragmentShaderData;
        }
        
        GLuint vertecShader;
        GLuint fragmentShader;
        GLuint programe;
        GLint linked;
        
        vertecShader = LoadShader(GL_VERTEX_SHADER, vertexShaderData.c_str());
        if (vertecShader == 0) {
            return 0;
        }
        
        fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderData.c_str());
        if (fragmentShaderStr == 0) {
            glDeleteShader(vertecShader);
            return 0;
        }
        
        programe = glCreateProgram();
        
        if (programe == 0) {
            return 0;
        }
        
        glAttachShader(programe, vertecShader);
        glAttachShader(programe, fragmentShader);
        
        glLinkProgram(programe);
        
        glGetProgramiv(programe, GL_LINK_STATUS, &linked);
        
        if (!linked) {
            GLint infoLen;
            glGetProgramiv(programe, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                
                char * infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetProgramInfoLog(programe, infoLen, NULL, infoLog);
                printf("%s", infoLog);
                free(infoLog);
                
            }
            
            glDeleteProgram(programe);
            return 0;
        }
        
        glDeleteShader(vertecShader);
        glDeleteShader(fragmentShader);
        
        return programe;
    }
    
    GLuint GLESBaseProgram::LoadShader(GLuint type, const char * shaderStr)
    {
        GLuint shader;
        GLint compiled;
        
        shader = glCreateShader(type);
        
        glShaderSource(shader, 1, &shaderStr, NULL);
        glCompileShader(shader);
        
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        
        if (!compiled) {
            
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen>1) {
                
                char * infoLog = (char *)malloc( sizeof(char) * infoLen );
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                
                printf("error compiling shader : %s", infoLog);
                
                free(infoLog);
            }
            
            glDeleteShader(shader);
            return 0;
        }
        
        return shader;
    }
    
    
    
    
#pragma mark - gl version platform
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}