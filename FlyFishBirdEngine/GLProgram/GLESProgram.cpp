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
    
    bool GLESProgram::Create()
    {
        std::string fshader("Shader.fsh");
        std::string vshader("Shader.vsh");
        
        if (!GLESBaseProgram::Create(vshader, fshader)) {
            return false;
        }
    
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
        
        ResetShader();
        
        
        return true;
    }
    
    void GLESProgram::Destory()
    {        
        GLESBaseProgram::Destory();
    }
    
    
#pragma mark - shader state
    
    void GLESProgram::ResetShader()
    {
        Matrix m[2];
        MatrixLoadIdentity(&m[0]);
        MatrixLoadIdentity(&m[1]);
        
        int f[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        
        glUniformMatrix4fv(m_mvpMatrixLocation, 1, GL_FALSE, (GLfloat *)m);
        glUniformMatrix4fv(m_mvMatrixLocation, 1, GL_FALSE, (GLfloat *)m);
        glUniformMatrix4fv(m_invTransposemvMatrixLocation, 1, GL_FALSE, (GLfloat *)m);
        
        glUniform1iv(m_enableTextureLocation, 2, f);
        glUniform1iv(m_enableTexutreMatrixLocation, 2, f);
        glUniformMatrix4fv(m_textureMatrixLocation, 2, GL_FALSE, (GLfloat *)m);
        
        glUniform4f(m_ambientSecenColorLocation, 0.0, 0.0, 0.0, 1.0);
        glUniform1iv(m_lightEnableStateLocation, 8, f);
        glUniform1iv(m_numLightsLocation, 8, f);
        glUniform1i(m_enableLightingLocation, f[0]);
        glUniform1i(m_lightModelTwoSideLocation, f[0]);
        glUniform1i(m_enableColorMaterialLocation, f[0]);
        
        glUniform1i(m_enableFogLocation, f[0]);
        glUniform1i(m_fogDensityLocation, f[0]);
        glUniform1i(m_fogStartLocation, f[0]);
        glUniform1i(m_fogEndLocation, f[0]);
        glUniform1i(m_fogEndLocation, f[0]);
        
        glUniform1i(m_xformEyePeopleLoction, f[0]);
        glUniform1i(m_rescaleNormalLocation, f[0]);
        glUniform1i(m_normalizeNormalLocation, f[0]);
        glUniform1i(m_rescaleNormaFactorLocation, f[0]);
        
        glUniform4f(m_ucpEqnLocation, 0.0, 0.0 ,0.0, 1.0);
        glUniform1i(m_enableUcpLocation, f[0]);
        
        glUniform1f(m_sTexcoord0Location, 0);
        glUniform1f(m_sTexcoord0Location, 1);
    }
    
    GLuint GLESProgram::GetPositionIndex()
    {
        return 1;
    }
    
    GLuint GLESProgram::GetTexcoord0Index()
    {
        return 2;
    }
    
    GLuint GLESProgram::GetTexcoord1Index()
    {
        return 3;
    }
    
    GLuint GLESProgram::GetColorIndex()
    {
        return 4;
    }
    
    GLuint GLESProgram::GetNormalIndex()
    {
        return 5;
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
        glGetUniformiv(m_enableTextureLocation, 2, v);
    }
}



