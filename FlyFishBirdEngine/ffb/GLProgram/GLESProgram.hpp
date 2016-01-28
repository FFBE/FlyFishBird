//
//  FFBGLESPrograme.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef FFBGLESProgram_hpp
#define FFBGLESProgram_hpp


#include <stdio.h>

#include <cstring>
#include <list>

#include "SimpleMath.h"
#include "BasicPtrClass.hpp"
#include "GLESBaseProgram.hpp"

namespace ffb {
    
    class GLESProgram:public GLESBaseProgram {
        
    public:

        
      
        CreateClassFunctions(GLESProgram);
        
        GLuint GetPositionIndex();
        GLuint GetTexcoord0Index();
        GLuint GetTexcoord1Index();
        GLuint GetColorIndex();
        GLuint GetNormalIndex();
        
        void SetMvpMatrix(Matrix mvpMatrix);
        
        void SetMvMatrix(Matrix mvMatrix);
        
        void EnableTexture(GLuint num);
        
        
        
    private:
        
        /* attribute location */
        
        GLuint          m_positionIndex;
        GLuint          m_texcoord0Index;
        GLuint          m_texcoord1Index;
        GLuint          m_colorIndex;
        GLuint          m_normalIndex;
        
        /* uniform location */
        
        /* matrix */
        // tht model-view-perspective matrix location
        GLuint          m_mvpMatrixLocation;
        // the model view matrix location
        GLuint          m_mvMatrixLocation;
        // inverse model-view matrix used to transform normal
        GLuint          m_invTransposemvMatrixLocation;
        
        
        /* texture */
        // enable texture
        GLuint          m_enableTextureLocation;
        // enable texture matrix
        GLuint          m_enableTexutreMatrixLocation;
        // two matrix
        GLuint          m_textureMatrixLocation;
        
        /* lighting */
        // material_state
        GLuint          m_materialStateLocation;
        // ambient_secen_color
        GLuint          m_ambientSecenColorLocation;
        // have eight light_state
        GLuint          m_lightStateLocation;
        // light_enable_state
        GLuint          m_lightEnableStateLocation;
        // num_lights
        GLuint          m_numLightsLocation;
        // enable_lighting
        GLuint          m_enableLightingLocation;
        // light_model_two_sided
        GLuint          m_lightModelTwoSideLocation;
        // enable_color_material
        GLuint          m_enableColorMaterialLocation;
        // sampler s_texcoord0
        GLuint          m_sTexcoord0Location;
        // sampler s_texcoord1
        GLuint          m_sTexcoord1Location;
        
        /* fog */
        // enable_fog
        GLuint          m_enableFogLocation;
        // fog_density
        GLuint          m_fogDensityLocation;
        // fog_start fog_end
        GLuint          m_fogStartLocation, m_fogEndLocation;
        // fog_mode     fog mode: linear, exp, or exp2
        GLuint          m_fogModeLocation;
        
        
        /* noraml */
        // xform_eye_p
        GLuint          m_xformEyePeopleLoction;
        // rescale_normal
        GLuint          m_rescaleNormalLocation;
        // normalize_normal
        GLuint          m_normalizeNormalLocation;
        // rescale_normal_factor
        GLuint          m_rescaleNormaFactorLocation;
        
        
        /* clip */
        // ucp_eqn
        GLuint          m_ucpEqnLocation;
        // enable_ucp
        GLuint          m_enableUcpLocation;
        
    };
}


#endif /* FFBGLESPrograme_hpp */
