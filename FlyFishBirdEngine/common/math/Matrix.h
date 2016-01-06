//
//  FFBMatrix.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>

#define PI 3.1415926535897932384626433832795f


typedef struct
{
    float m[4][4];
}Matrix;


//get identity martix
void MatrixLoadIdentity (Matrix *result);
//multiply matrix
void MatrixMultiply(Matrix *result, Matrix *m1, Matrix *m2);


//transform martrix
void Rotate(Matrix *result, float angle, float x, float y, float z);
void Scale(Matrix *result, float sx, float sy, float sz);
void Translate(Matrix *result, float tx, float ty, float tz);


int GenCube ( float scale, float **vertices, float **normals, float **texCoords, int **indices );

#endif /* FFBMatrix_hpp */
