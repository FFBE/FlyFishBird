//
//  Shader.fsh
//  gles2.0
//
//  Created by weitoo on 15/10/31.
//  Copyright © 2015年 FlyFishBird. All rights reserved.
//

#version 300 es

precision mediump float;

#define NUM_TEXTURES            2

const int           indx_zero = 0;
const int           indx_one = 1;

uniform bool        enable_tex[NUM_TEXTURES];           // texture enables

in vec2            v_texcoord[NUM_TEXTURES];
in vec4            v_front_color;
in vec4            v_back_color;
in float           v_fog_factor;
in float           v_ucp_factor;

layout(location = 0) out vec4 outColor;

uniform sampler2D s_texcoord0;
uniform sampler2D s_texcoord1;


void main()
{
    outColor = v_front_color;
    if (enable_tex[indx_zero])
        outColor = texture(s_texcoord0, v_texcoord[indx_zero]);
    else if (enable_tex[indx_one])
        outColor = texture(s_texcoord1, v_texcoord[indx_one]);
}