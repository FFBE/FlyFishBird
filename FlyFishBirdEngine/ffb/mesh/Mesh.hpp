//
//  FFBMesh.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/12/3.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef FFBMesh_hpp
#define FFBMesh_hpp

#include <stdio.h>
#include <vector>
#include <OpenGLES/gltypes.h>
#include <OpenGLES/ES3/gl.h>

#include "Renderer.hpp"
#include "SimpleMath.h"
#include "GLESProgram.hpp"



#define VERTEX_POS_INDX     0

namespace ffb {
   
    typedef enum
    {
        FFBDrawTypeLines            =  GL_LINES,
        FFBDrawTypeLine_Loop        =  GL_LINE_LOOP,
        FFBDrawTypeLIne_Strip       =  GL_LINE_STRIP,
        FFBDrawTypeTriangles        =  GL_TRIANGLES,
        FFBDrawTypeTriangle_Strip   =  GL_TRIANGLE_STRIP,
        FFBDrawTypeTriangle_Fan     =  GL_TRIANGLE_FAN,
        FFBDrawTypePoints           =  FFBDrawTypeTriangle_Fan+1,
    }FFBDrawType;
    
    typedef enum
    {
        VerticesStepTwo = 2,            //x, y
        VerticesStepThree = 3           //x, y, z
    }VerticesStep;
    
    class Mesh : public Renderer {
        
    public:
        
        struct MeshAttribute
        {
            int             numberOfIndeices;
            int             numberOfVertices;
            GLuint          * indices;
            GLfloat         * vertices;
            FFBDrawType     drawType;
            VerticesStep    verticesStep;
        };
        
        
        //the key in default create function is defalut program
        CreateClassFunctions(Mesh);
       
        
        virtual void Render();

        
        //set shape data
        
        void AddShapData(GLuint * indices, int numberOfIndeices, GLfloat * vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep);
        
        
        /* color */
        
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
        Color GetColor();
        
        
    private:
        
        typedef std::vector<MeshAttribute> MeshAttributeVector;
        
        //shader color
        Color                   m_shaderColor;
        //vbo
        GLuint                  * m_vboids;
        
        MeshAttributeVector     m_meshVector;
        
    };
}




#endif /* FFBMesh_hpp */
