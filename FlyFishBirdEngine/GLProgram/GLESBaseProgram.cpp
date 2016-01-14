//
//  GLESBaseProgram.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/17.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GLESBaseProgram.hpp"

namespace ffb {
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
        
        return true;
    }
    
    bool GLESBaseProgram::Create(std::string vertexShaderFile, std::string fragmentShaderFile)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_programObject = LoadGLESProgram(ReadFile(vertexShaderFile.c_str()), ReadFile(fragmentShaderFile.c_str()));
        
        if (m_programObject == 0) {
            std::cout<<"failed to load create programe"<<std::endl;
            return false;
        }
        
        return true;
    }
    
    void GLESBaseProgram::Destory()
    {
        BasicPtrClass::Destory();
    }
    
    bool GLESBaseProgram::Create(const char *vertecShader, const char *fragmentShader)
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        m_programObject = LoadGLESProgram(vertecShader, vertecShader);
        return true;
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
    
    GLuint GLESBaseProgram::LoadGLESProgram(const char * vertecShaderStr, const char * fragmentShaderStr)
    {
        GLuint vertecShader;
        GLuint fragmentShader;
        GLuint programe;
        GLint linked;
        
        vertecShader = LoadShader(GL_VERTEX_SHADER, vertecShaderStr);
        if (vertecShader == 0) {
            return 0;
        }
        
        fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderStr);
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
    
    
    
    
}