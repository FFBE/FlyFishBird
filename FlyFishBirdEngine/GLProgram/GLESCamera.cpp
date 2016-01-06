//
//  GLESCamera.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 15/11/24.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#include "GLESCamera.hpp"
#include <math.h>

namespace ffb {
    
    bool GLESCamera::Create()
    {
        if (!BasicPtrClass::Create()) {
            return false;
        }
        
        MatrixLoadIdentity(&m_cameraMatrix);

        return true;
    }
    
    void GLESCamera::Destory()
    {
        BasicPtrClass::Destory();
    }
    
    void GLESCamera::Clear()
    {
        BasicPtrClass::Clear();
    }
    
    Matrix GLESCamera::GetCameraMatrix()
    {
        return m_cameraMatrix;
    }
    
    void  GLESCamera::CameraFrustum ( float left, float right, float bottom, float top, float nearZ, float farZ )
    {
        float       deltaX = right - left;
        float       deltaY = top - bottom;
        float       deltaZ = farZ - nearZ;
        Matrix    frust;
        
        if ( ( nearZ <= 0.0f ) || ( farZ <= 0.0f ) ||
            ( deltaX <= 0.0f ) || ( deltaY <= 0.0f ) || ( deltaZ <= 0.0f ) )
        {
            return;
        }
        
        frust.m[0][0] = 2.0f * nearZ / deltaX;
        frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;
        
        frust.m[1][1] = 2.0f * nearZ / deltaY;
        frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;
        
        frust.m[2][0] = ( right + left ) / deltaX;
        frust.m[2][1] = ( top + bottom ) / deltaY;
        frust.m[2][2] = - ( nearZ + farZ ) / deltaZ;
        frust.m[2][3] = -1.0f;
        
        frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
        frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;
        
        MatrixMultiply (&m_cameraMatrix, &frust, &m_cameraMatrix );
    }
    
    void GLESCamera::CameraPerspective ( float fovy, float aspect, float nearZ, float farZ )
    {
        float frustumW, frustumH;
        
        frustumH = tanf ( fovy / 360.0f * PI ) * nearZ;
        frustumW = frustumH * aspect;
        
        CameraFrustum (-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
    }
    
    void GLESCamera::CameraOrtho ( float left, float right, float bottom, float top, float nearZ, float farZ )
    {
        float       deltaX = right - left;
        float       deltaY = top - bottom;
        float       deltaZ = farZ - nearZ;
        Matrix    ortho;
        
        if ( ( deltaX == 0.0f ) || ( deltaY == 0.0f ) || ( deltaZ == 0.0f ) )
        {
            return;
        }
        
        MatrixLoadIdentity ( &ortho );
        ortho.m[0][0] = 2.0f / deltaX;
        ortho.m[3][0] = - ( right + left ) / deltaX;
        ortho.m[1][1] = 2.0f / deltaY;
        ortho.m[3][1] = - ( top + bottom ) / deltaY;
        ortho.m[2][2] = -2.0f / deltaZ;                 // 2.0f / deltaZ
        ortho.m[3][2] = - ( nearZ + farZ ) / deltaZ;
        
        MatrixMultiply ( &m_cameraMatrix, &ortho, &m_cameraMatrix );
    }
    
    void GLESCamera::CameraMatrixLookAt ( float posX,    float posY,    float posZ,
                                          float lookAtX, float lookAtY, float lookAtZ,
                                          float upX,     float upY,     float upZ )
    {
        float axisX[3], axisY[3], axisZ[3];
        float length;
        
        // axisZ = lookAt - pos
        axisZ[0] = lookAtX - posX;
        axisZ[1] = lookAtY - posY;
        axisZ[2] = lookAtZ - posZ;
        
        // normalize axisZ
        length = sqrtf ( axisZ[0] * axisZ[0] + axisZ[1] * axisZ[1] + axisZ[2] * axisZ[2] );
        
        if ( length != 0.0f )
        {
            axisZ[0] /= length;
            axisZ[1] /= length;
            axisZ[2] /= length;
        }
        
        // axisX = up X axisZ
        axisX[0] = upY * axisZ[2] - upZ * axisZ[1];
        axisX[1] = upZ * axisZ[0] - upX * axisZ[2];
        axisX[2] = upX * axisZ[1] - upY * axisZ[0];
        
        // normalize axisX
        length = sqrtf ( axisX[0] * axisX[0] + axisX[1] * axisX[1] + axisX[2] * axisX[2] );
        
        if ( length != 0.0f )
        {
            axisX[0] /= length;
            axisX[1] /= length;
            axisX[2] /= length;
        }
        
        // axisY = axisZ x axisX
        axisY[0] = axisZ[1] * axisX[2] - axisZ[2] * axisX[1];
        axisY[1] = axisZ[2] * axisX[0] - axisZ[0] * axisX[2];
        axisY[2] = axisZ[0] * axisX[1] - axisZ[1] * axisX[0];
        
        // normalize axisY
        length = sqrtf ( axisY[0] * axisY[0] + axisY[1] * axisY[1] + axisY[2] * axisY[2] );
        
        if ( length != 0.0f )
        {
            axisY[0] /= length;
            axisY[1] /= length;
            axisY[2] /= length;
        }
        
        memset ( &m_cameraMatrix, 0x0, sizeof ( Matrix ) );
        
        m_cameraMatrix.m[0][0] = -axisX[0];
        m_cameraMatrix.m[0][1] =  axisY[0];
        m_cameraMatrix.m[0][2] = -axisZ[0];
        
        m_cameraMatrix.m[1][0] = -axisX[1];
        m_cameraMatrix.m[1][1] =  axisY[1];
        m_cameraMatrix.m[1][2] = -axisZ[1];
        
        m_cameraMatrix.m[2][0] = -axisX[2];
        m_cameraMatrix.m[2][1] =  axisY[2];
        m_cameraMatrix.m[2][2] = -axisZ[2];
        
        // translate (-posX, -posY, -posZ)
        m_cameraMatrix.m[3][0] =  axisX[0] * posX + axisX[1] * posY + axisX[2] * posZ;
        m_cameraMatrix.m[3][1] = -axisY[0] * posX - axisY[1] * posY - axisY[2] * posZ;
        m_cameraMatrix.m[3][2] =  axisZ[0] * posX + axisZ[1] * posY + axisZ[2] * posZ;
        m_cameraMatrix.m[3][3] = 1.0f;
    }
    
    
    
    
    void GLESCamera::CameraMove(float x, float y, float z)
    {
        Translate(&m_cameraMatrix, x, y, z);
    }
    
    void GLESCamera::CameraScale(float x, float y, float z)
    {
        Scale(&m_cameraMatrix, x, y, z);
    }
    
    void GLESCamera::CameraRoate(float angle, float x, float y, float z)
    {
        Rotate(&m_cameraMatrix, angle, x, y, z);
    }
}

