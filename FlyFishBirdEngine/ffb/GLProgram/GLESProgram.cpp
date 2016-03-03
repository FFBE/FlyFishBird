//
//  FFBGLESProgram.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GLESProgram.hpp"

#include "GameController.hpp"
#include <stdlib.h>
#include <cstring>
#include <fstream>

#include "ReadFile.h"


namespace ffb {
    
    void GLESProgram::Clear()
    {
        GLESBaseProgram::Clear();
    }
    
    void GLESProgram::Destory()
    {
        GLESBaseProgram::Destory();
    }

    
    bool GLESProgram::Create()
    {
        std::string fshader("Shader.fsh");
        std::string vshader("Shader.vsh");
        
        if (!GLESBaseProgram::Create(vshader, fshader)) {
            return false;
        }
        
        //attribute
        
        m_positionIndex = glGetAttribLocation(m_programObject, "a_position");
        m_texcoord0Index = glGetAttribLocation(m_programObject, "a_texcoord0");
        m_texcoord1Index = glGetAttribLocation(m_programObject, "a_texcoord1");
        m_colorIndex = glGetAttribLocation(m_programObject, "a_color");
        m_normalIndex = glGetAttribLocation(m_programObject, "a_normal");

        
        
        //uniform
    
        m_mvpMatrixLocation = glGetUniformLocation(m_programObject, "mvp_matrix");
        
        m_mvMatrixLocation = glGetUniformLocation(m_programObject, "modelview_matrix");
        
        m_invTransposemvMatrixLocation = glGetUniformLocation(m_programObject, "inv_transpose_modelview_matrix");
        
        m_enableTextureLocation = glGetUniformLocation(m_programObject, "enable_tex");
        
        m_enableTexutreMatrixLocation = glGetUniformLocation(m_programObject, "enable_tex_matrix");
        
        m_textureMatrixLocation = glGetUniformLocation(m_programObject, "tex_matrix");
        
//        m_materialStateLocation  is  a  uniform block
        
        m_ambientSecenColorLocation = glGetUniformLocation(m_programObject, "ambient_secen_color");
        
//        m_lightStateLocation is a uniform block
        
        m_lightEnableStateLocation = glGetUniformLocation(m_programObject, "light_enable_state");
        
        m_numLightsLocation = glGetUniformLocation(m_programObject, "num_lights");
        
        m_enableLightingLocation = glGetUniformLocation(m_programObject, "enable_lighting");
    
        m_lightModelTwoSideLocation = glGetUniformLocation(m_programObject, "light_model_two_sided");
        
        m_enableColorMaterialLocation = glGetUniformLocation(m_programObject, "enable_color_material");
        
        m_sTexcoord0Location = glGetUniformLocation(m_programObject, "s_texcoord0");
        
        m_sTexcoord1Location = glGetUniformLocation(m_programObject, "s_texcoord1");
        
        m_enableFogLocation = glGetUniformLocation(m_programObject, "enable_fog");
        
        m_fogDensityLocation = glGetUniformLocation(m_programObject, "fog_density");
        
        m_fogStartLocation = glGetUniformLocation(m_programObject, "fog_start");
        
        m_fogEndLocation = glGetUniformLocation(m_programObject, "fog_end");
        
        m_fogModeLocation = glGetUniformLocation(m_programObject, "fog_model");
        
        m_xformEyePeopleLoction = glGetUniformLocation(m_programObject, "xform_eye_p");
        
        m_rescaleNormalLocation = glGetUniformLocation(m_programObject, "rescale_normal");
        
        m_normalizeNormalLocation = glGetUniformLocation(m_programObject, "normalize_normal");
        
        m_rescaleNormaFactorLocation = glGetUniformLocation(m_programObject, "rescale_normal_factor");
        
        m_ucpEqnLocation = glGetUniformLocation(m_programObject, "ucp_eqn");
        
        m_enableUcpLocation = glGetUniformLocation(m_programObject, "enable_ucp");
        
        return true;
    }
    
#pragma mark - shader state
    
    
    GLuint GLESProgram::GetPositionIndex()
    {
        return m_positionIndex;
    }
    
    GLuint GLESProgram::GetTexcoord0Index()
    {
        return m_texcoord0Index;
    }
    
    GLuint GLESProgram::GetTexcoord1Index()
    {
        return m_texcoord1Index;
    }
    
    GLuint GLESProgram::GetColorIndex()
    {
        return m_colorIndex;
    }
    
    GLuint GLESProgram::GetNormalIndex()
    {
        return m_normalIndex;
    }
    
    void GLESProgram::SetMvpMatrix(Matrix mvpMatrix)
    {
        glUniformMatrix4fv(m_mvpMatrixLocation, 1, GL_FALSE, (GLfloat *)&mvpMatrix.m[0][0]);
    }
    
    void GLESProgram::SetMvMatrix(Matrix mvMatrix)
    {
        glUniformMatrix4fv(m_mvMatrixLocation, 1, GL_FALSE, (GLfloat *)&mvMatrix.m[0][0]);
    }
    
    void GLESProgram::EnableTexture(GLuint num)
    {
        int v[2] = {0, 0};
        if (num == 1) {
            v[0] = 1;
        }
        else if (num == 2)
        {
            v[0] = 1, v[1] = 1 ;
        }
        glUniform1iv(m_enableTextureLocation, 2, v);
    }
}



