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
            GLfloat         lineWidth;
            Color           color;
        };
        
        
        //the key in default create function is defalut program
        CreateClassFunctions(Mesh);
       
        
        virtual void Render();

        
        //set shape data
        
        void AddShapData(GLuint * indices, int numberOfIndeices, GLfloat * vertices, int numberOfVertices, FFBDrawType type, VerticesStep verticesStep, GLfloat lineWidth);
        
        
        /* color */
        
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
        Color GetColor();
        
        void RemoveAllShap();
        
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
