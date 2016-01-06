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

#include "BasicPtrClass.hpp"
#include "SimpleMath.h"
#include "GLESProgram.hpp"

#include <OpenGLES/gltypes.h>
#include <OpenGLES/ES3/gl.h>

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
    
    
    class Mesh : public BasicPtrClass {
        
    public:
        
        //the key in default create function is defalut program
        CreateClassFunctions(Mesh);
        bool Create(short key);
        bool Create(GLESProgram * programe);
        
        virtual void Render();

        
        //set shape data
        void SetDrawType(FFBDrawType type);
        
        void SetVerticesStep(unsigned int step);
        
        void SetIndices(GLuint * indices, int numberOfIndeices);
        
        void SetVertices(GLfloat * vertices, int numberOfVertices);
        
        void SetShapData(GLuint * indices, int numberOfIndeices, GLfloat * vertices, int numberOfVertices, FFBDrawType type);
        
        //get shape data
        FFBDrawType GetDrawType();
        
        unsigned int GetVerticesStep();
        
        int GetNumberIndeices();
        
        GLuint * GetIndices();
        
        GLfloat * GetVertices();
        
        
        /*position*/
        void SetPosition(Point point);
        void SetPosition(float x, float y);
        Point  GetPosition();
        
        void SetSize(Size size);
        void SetSize(float width, float height);
        Size  GetSize();
        
        void SetScale(float scale);
        void SetScale(float scaleX, float scaleY);
        void SetScale(Point scale);
        Point GetScale();
        
        void SetRotate(float rotate);
        float GetRotate();
        
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
        Color GetColor();
        
        
        
        Matrix GetMvpMatrix();
        
    protected:
       
        /* position */
        //center point default (0, 0)
        Point            m_point;
        
        //scale default 1
        Point            m_scale;
        
        //360r   default 0    clock wise
        float               m_rotate;
        
        
        GLESProgram        *m_glprogram;
        
        Matrix      m_mvpMatrix;

        
    private:
        
        /* vertex data */
        
        //shape vertex index of sequence
        GLuint              m_numberOfIndeices;
        //vertex index
        GLuint             *m_indices;
        //vertex data
        GLfloat            *m_vertices;
        //vertex step , default is 3, means x, y, z
        unsigned int        m_verticesStep;
        //shader color
        Color            m_shaderColor;
        //vbo
        GLuint              m_numberOfVertices;
        /* matrix */
        // model-view-perspective matrix
        
        GLuint             m_vboids[2];
        
        FFBDrawType m_drawType;
        
    };
}




#endif /* FFBMesh_hpp */
