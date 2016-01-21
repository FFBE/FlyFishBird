//
//  FFBMatrix.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "Matrix.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

void MatrixLoadIdentity(Matrix *result)
{
    memset(result, 0x0, sizeof(Matrix));
    result->m[0][0] = 1.0f;
    result->m[1][1] = 1.0f;
    result->m[2][2] = 1.0f;
    result->m[3][3] = 1.0f;
}

void MatrixMultiply(Matrix *result, Matrix *m1, Matrix *m2)
{
    if (result == NULL || m1 == NULL || m2 == NULL) {
        printf("matrix cannot be NULL");
        return;
    }
    
    int     i;
    Matrix  tmp;
    
    for (i = 0; i<4; i++) {
        tmp.m[i][0] = m1->m[i][0] * m2->m[0][0]+
        m1->m[i][1] * m2->m[1][0]+
        m1->m[i][2] * m2->m[2][0]+
        m1->m[i][3] * m2->m[3][0];
        
        tmp.m[i][1] = m1->m[i][0] * m2->m[0][1]+
        m1->m[i][1] * m2->m[1][1]+
        m1->m[i][2] * m2->m[2][1]+
        m1->m[i][3] * m2->m[3][1];
        
        tmp.m[i][2] = m1->m[i][0] * m2->m[0][2]+
        m1->m[i][1] * m2->m[1][2]+
        m1->m[i][2] * m2->m[2][2]+
        m1->m[i][3] * m2->m[3][2];
        
        tmp.m[i][3] = m1->m[i][0] * m2->m[0][3]+
        m1->m[i][1] * m2->m[1][3]+
        m1->m[i][2] * m2->m[2][3]+
        m1->m[i][3] * m2->m[3][3];
    }
    
    memcpy(result, &tmp, sizeof(Matrix));
}


void Rotate(Matrix *result, float angle, float x, float y, float z)
{
    float sinAngle, cosAngle;
    float mag = sqrt(x*x + y*y + z*z);
    
    sinAngle = sinf ( angle * PI / 180.0f );
    cosAngle = cosf ( angle * PI / 180.0f );
//    printf("%f\n", sinAngle);
//    printf("%f\n", cosAngle);

    if (mag > 0)
    {
        float xx, yy, zz, xy, yz, zx, xs, ys, zs;
        float oneMinusCos;
        Matrix rotMat;
        
        //转化为单位向量的x，y，z
        x /= mag;
        y /= mag;
        z /= mag;
        
        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;
        
        rotMat.m[0][0] = ( oneMinusCos * xx ) + cosAngle;
        rotMat.m[0][1] = ( oneMinusCos * xy ) - zs;
        rotMat.m[0][2] = ( oneMinusCos * zx ) + ys;
        rotMat.m[0][3] = 0.0F;
        
        rotMat.m[1][0] = ( oneMinusCos * xy ) + zs;
        rotMat.m[1][1] = ( oneMinusCos * yy ) + cosAngle;
        rotMat.m[1][2] = ( oneMinusCos * yz ) - xs;
        rotMat.m[1][3] = 0.0F;
        
        rotMat.m[2][0] = ( oneMinusCos * zx ) - ys;
        rotMat.m[2][1] = ( oneMinusCos * yz ) + xs;
        rotMat.m[2][2] = ( oneMinusCos * zz ) + cosAngle;
        rotMat.m[2][3] = 0.0F;
        
        rotMat.m[3][0] = 0.0F;
        rotMat.m[3][1] = 0.0F;
        rotMat.m[3][2] = 0.0F;
        rotMat.m[3][3] = 1.0F;
        
        MatrixMultiply ( result, &rotMat, result );
    }
}


void Scale(Matrix *result, float sx, float sy, float sz)
{
    result->m[0][0] *= sx;
    result->m[0][1] *= sx;
    result->m[0][2] *= sx;
    result->m[0][3] *= sx;
    
    result->m[1][0] *= sy;
    result->m[1][1] *= sy;
    result->m[1][2] *= sy;
    result->m[1][3] *= sy;
    
    result->m[2][0] *= sz;
    result->m[2][1] *= sz;
    result->m[2][2] *= sz;
    result->m[2][3] *= sz;
}


void Translate(Matrix *result, float tx, float ty, float tz)
{
    result->m[3][0] += ( result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz );
    result->m[3][1] += ( result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz );
    result->m[3][2] += ( result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz );
    result->m[3][3] += ( result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz );
}


int GenCube ( float scale, float **vertices, float **normals, float **texCoords, unsigned int **indices )
{
    int i;
    int numVertices = 24;
    int numIndices = 36;
    
    float cubeVerts[] =
    {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
    };
    
    float cubeNormals[] =
    {
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    
    float cubeTex[] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    
    // Allocate memory for buffers
    if ( vertices != NULL )
    {
        *vertices = (float *)malloc ( sizeof ( float ) * 3 * numVertices );
        memcpy ( *vertices, cubeVerts, sizeof ( cubeVerts ) );
        
        for ( i = 0; i < numVertices * 3; i++ )
        {
            ( *vertices ) [i] *= scale;
        }
    }
    
    if ( normals != NULL )
    {
        *normals = (float *)malloc ( sizeof ( float ) * 3 * numVertices );
        memcpy ( *normals, cubeNormals, sizeof ( cubeNormals ) );
    }
    
    if ( texCoords != NULL )
    {
        *texCoords = (float *)malloc ( sizeof ( float ) * 2 * numVertices );
        memcpy ( *texCoords, cubeTex, sizeof ( cubeTex ) ) ;
    }
    
    
    // Generate the indices
    if ( indices != NULL )
    {
        unsigned int cubeIndices[] =
        {
            0, 2, 1,
            0, 3, 2,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 15, 14,
            12, 14, 13,
            16, 17, 18,
            16, 18, 19,
            20, 23, 22,
            20, 22, 21
        };
        
        *indices = (unsigned int *)malloc ( sizeof ( unsigned int ) * numIndices );
        memcpy ( *indices, cubeIndices, sizeof ( cubeIndices ) );
    }
    
    return numIndices;
}