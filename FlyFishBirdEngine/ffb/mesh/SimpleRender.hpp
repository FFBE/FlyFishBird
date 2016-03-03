//
//  SimpleRender.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/2/23.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef SimpleRender_hpp
#define SimpleRender_hpp

#include <stdio.h>
#include "Renderer.hpp"

namespace ffb {
    
    class SimpleRender: public Renderer {
        
        
        
    public:
        
        CreateClassFunctions(SimpleRender);
        
        bool Create(int numberOfIndeices, int numberOfVertices, GLuint *indices, GLfloat *vertices, FFBDrawType drawType, VerticesStep verticesStep);
        
        void SetIndices(int numberOfIndices, GLuint * indices);
        void SetVertices( int numberOfVertices, GLfloat * vertices, VerticesStep verticesStep);
        void SetDrawType( FFBDrawType drawType );
        void SetLineWidth( float lineWidth );
        
        
        void SetColor(float r, float g, float b, float a);
        void SetColor(Color color);
        Color GetColor();
        
        virtual void Render();
        
    protected:
        
        int             m_numberOfIndeices;
        int             m_numberOfVertices;
        GLuint          * m_indices;
        GLfloat         * m_vertices;
        FFBDrawType     m_drawType;
        VerticesStep    m_verticesStep;
        GLfloat         m_lineWidth;
        
        GLuint          m_vboids[2];
        
    private:
        
        Color           m_color;
        
    };
    
}



#endif /* RenderRect_hpp */
