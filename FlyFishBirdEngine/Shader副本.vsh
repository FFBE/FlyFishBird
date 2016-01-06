


//Position Texture Color shader
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; void main() { gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord); }
// Position Texture Color without MVP shader
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_PMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; void main() { gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord); }
// Position Texture Color alpha test
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform float CC_alpha_value; void main() { vec4 texColor = texture2D(CC_Texture0, v_texCoord);
    
    if ( texColor.a <= CC_alpha_value ) discard; gl_FragColor = texColor * v_fragmentColor; }
// Position Texture Color alpha test
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_PMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform float CC_alpha_value; void main() { vec4 texColor = texture2D(CC_Texture0, v_texCoord);
    
    if ( texColor.a <= CC_alpha_value ) discard; gl_FragColor = texColor * v_fragmentColor; }
// Position, Color shader
attribute vec4 a_position; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; void main() { gl_FragColor = v_fragmentColor; }
attribute vec4 a_position; attribute vec4 a_color; attribute vec2 a_texCoord;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; gl_PointSize = a_texCoord.x; v_fragmentColor = a_color; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; void main() { gl_FragColor = v_fragmentColor; }
// Position, Color shader no MVP
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_PMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; void main() { gl_FragColor = v_fragmentColor; }
// Position Texture shader
attribute vec4 a_position; attribute vec2 a_texCoord;
#ifdef GL_ES
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec2 v_texCoord; void main() { gl_FragColor = texture2D(CC_Texture0, v_texCoord); }
// Position, Texture attribs, 1 Color as uniform shader
attribute vec4 a_position; attribute vec2 a_texCoord;
#ifdef GL_ES
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
uniform vec4 u_color; varying vec2 v_texCoord; void main() { gl_FragColor = texture2D(CC_Texture0, v_texCoord) * u_color; }
// Position Texture A8 Color shader
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; void main() { gl_FragColor = vec4( v_fragmentColor.rgb, v_fragmentColor.a * texture2D(CC_Texture0, v_texCoord).a ); }
// Position and 1 color passed as a uniform (to simulate glColor4ub )
attribute vec4 a_position; uniform vec4 u_color; uniform float u_pointSize;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; gl_PointSize = u_pointSize; v_fragmentColor = u_color; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; void main() { gl_FragColor = v_fragmentColor; }
ShaderPositionLengthTextureColor

#ifdef GL_ES
attribute mediump vec4 a_position; attribute mediump vec2 a_texcoord; attribute mediump vec4 a_color; varying mediump vec4 v_color; varying mediump vec2 v_texcoord;
#else
attribute vec4 a_position; attribute vec2 a_texcoord; attribute vec4 a_color; varying vec4 v_color; varying vec2 v_texcoord;
#endif
void main() { v_color = vec4(a_color.rgb * a_color.a, a_color.a); v_texcoord = a_texcoord; gl_Position = CC_MVPMatrix * a_position; }

#ifdef GL_ES
varying mediump vec4 v_color; varying mediump vec2 v_texcoord;
#else
varying vec4 v_color; varying vec2 v_texcoord;
#endif
void main() { gl_FragColor = v_color*step(0.0, 1.0 - length(v_texcoord)); }
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform vec4 u_textColor; void main() { vec4 color = texture2D(CC_Texture0, v_texCoord); float dist = color.a; float width = 0.04; float alpha = smoothstep(0.5-width, 0.5+width, dist) * u_textColor.a; gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb,alpha); }
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform vec4 u_effectColor; uniform vec4 u_textColor; void main() { float dist = texture2D(CC_Texture0, v_texCoord).a; float width = 0.04; float alpha = smoothstep(0.5-width, 0.5+width, dist); float mu = smoothstep(0.5, 1.0, sqrt(dist)); vec4 color = u_effectColor*(1.0-alpha) + u_textColor*alpha; gl_FragColor = v_fragmentColor * vec4(color.rgb, max(alpha,mu)*color.a); }
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_PMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES

precision mediump float;

#endif



varying vec4 v_fragmentColor;

varying vec2 v_texCoord;



void main(void)

{
    
    vec4 c = texture2D(CC_Texture0, v_texCoord);
    
    gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b);
    
    gl_FragColor.w = c.w;
    
}

attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform vec4 u_textColor; void main() { gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb, u_textColor.a * texture2D(CC_Texture0, v_texCoord).a ); }
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec4 a_color;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor; varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor; varying vec2 v_texCoord;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_fragmentColor = a_color; v_texCoord = a_texCoord; }

#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor; varying vec2 v_texCoord; uniform vec4 u_effectColor; uniform vec4 u_textColor; void main() { vec4 sample = texture2D(CC_Texture0, v_texCoord); float fontAlpha = sample.a; float outlineAlpha = sample.r; if ((fontAlpha + outlineAlpha) > 0.0){ vec4 color = u_textColor * fontAlpha + u_effectColor * (1.0 - fontAlpha); gl_FragColor = v_fragmentColor * vec4( color.rgb,max(fontAlpha,outlineAlpha)*color.a); } else { discard; } }
attribute vec4 a_position; attribute vec2 a_texCoord; varying vec2 TextureCoordOut; void main(void) { gl_Position = CC_MVPMatrix * a_position; TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; }

#ifdef GL_ES
varying lowp vec4 DestinationColor;
#else
varying vec4 DestinationColor;
#endif
uniform vec4 u_color; void main(void) { gl_FragColor = u_color; }
attribute vec4 a_position; attribute vec2 a_texCoord; varying vec2 TextureCoordOut; void main(void) { gl_Position = CC_MVPMatrix * a_position; TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; }

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color; void main(void) { gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color; }
attribute vec3 a_position; attribute vec4 a_blendWeight; attribute vec4 a_blendIndex; attribute vec2 a_texCoord; const int SKINNING_JOINT_COUNT = 60; uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3]; varying vec2 TextureCoordOut; vec4 getPosition() { float blendWeight = a_blendWeight[0]; int matrixIndex = int (a_blendIndex[0]) * 3; vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight; vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight; vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[1]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[1]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[2]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[2]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[3]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[3]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; } } } vec4 _skinnedPosition; vec4 postion = vec4(a_position, 1.0); _skinnedPosition.x = dot(postion, matrixPalette1); _skinnedPosition.y = dot(postion, matrixPalette2); _skinnedPosition.z = dot(postion, matrixPalette3); _skinnedPosition.w = postion.w; return _skinnedPosition; } void main() { vec4 position = getPosition(); gl_Position = CC_MVPMatrix * position; TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; }

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color; void main(void) { gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color; }

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
#endif
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec3 a_normal; varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif
void main(void) { vec4 ePosition = CC_MVMatrix * a_position;
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz - ePosition.xyz; }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz; }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    v_normal = CC_NormalMatrix * a_normal;
#endif
    TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; gl_Position = CC_PMatrix * ePosition; }

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM]; uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM]; uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM]; uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
#endif
uniform vec3 u_AmbientLightSourceColor;
#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying mediump vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying mediump vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying mediump vec3 v_normal;
#endif

#else
varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif

#endif
uniform vec4 u_color; vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation) { float diffuse = max(dot(normalVector, lightDirection), 0.0); vec3 diffuseColor = lightColor * diffuse * attenuation; return diffuseColor; } void main(void) {
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    vec3 normal = normalize(v_normal);
#endif
    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i) { vec3 lightDirection = normalize(u_DirLightSourceDirection[i] * 2.0); combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0); }
#endif
    
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation); }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]); vec3 spotLightDirection = normalize(u_SpotLightSourceDirection[i] * 2.0); float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection); attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos); attenuation = clamp(attenuation, 0.0, 1.0); combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation); }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    gl_FragColor = u_color * combinedColor;
#else
    gl_FragColor = u_color;
#endif
}

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
#endif
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec3 a_normal; varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif
void main(void) { vec4 ePosition = CC_MVMatrix * a_position;
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz - ePosition.xyz; }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz; }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    v_normal = CC_NormalMatrix * a_normal;
#endif
    TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; gl_Position = CC_PMatrix * ePosition; }

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM]; uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM]; uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM]; uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
#endif
uniform vec3 u_AmbientLightSourceColor;
#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying mediump vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying mediump vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying mediump vec3 v_normal;
#endif

#else
varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif

#endif
uniform vec4 u_color; vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation) { float diffuse = max(dot(normalVector, lightDirection), 0.0); vec3 diffuseColor = lightColor * diffuse * attenuation; return diffuseColor; } void main(void) {
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    vec3 normal = normalize(v_normal);
#endif
    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i) { vec3 lightDirection = normalize(u_DirLightSourceDirection[i] * 2.0); combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0); }
#endif
    
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation); }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]); vec3 spotLightDirection = normalize(u_SpotLightSourceDirection[i] * 2.0); float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection); attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos); attenuation = clamp(attenuation, 0.0, 1.0); combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation); }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color * combinedColor;
#else
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
#endif
}

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
#endif
attribute vec3 a_position; attribute vec4 a_blendWeight; attribute vec4 a_blendIndex; attribute vec2 a_texCoord; attribute vec3 a_normal; const int SKINNING_JOINT_COUNT = 60; uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3]; varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif
varying vec3 v_normal; void getPositionAndNormal(out vec4 position, out vec3 normal) { float blendWeight = a_blendWeight[0]; int matrixIndex = int (a_blendIndex[0]) * 3; vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight; vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight; vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[1]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[1]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[2]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[2]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; blendWeight = a_blendWeight[3]; if (blendWeight > 0.0) { matrixIndex = int(a_blendIndex[3]) * 3; matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight; matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight; matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight; } } } vec4 p = vec4(a_position, 1.0); position.x = dot(p, matrixPalette1); position.y = dot(p, matrixPalette2); position.z = dot(p, matrixPalette3); position.w = p.w;
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    vec4 n = vec4(a_normal, 0.0); normal.x = dot(n, matrixPalette1); normal.y = dot(n, matrixPalette2); normal.z = dot(n, matrixPalette3);
#endif
} void main() { vec4 position; vec3 normal; getPositionAndNormal(position, normal); vec4 ePosition = CC_MVMatrix * position;
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz- ePosition.xyz; }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz; }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    v_normal = CC_NormalMatrix * normal;
#endif
    TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; gl_Position = CC_PMatrix * ePosition; }

#define MAX_DIRECTIONAL_LIGHT_NUM 1

#define MAX_POINT_LIGHT_NUM 1

#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM]; uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM]; uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM]; uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM]; uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
#endif
uniform vec3 u_AmbientLightSourceColor;
#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying mediump vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying mediump vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying mediump vec3 v_normal;
#endif

#else
varying vec2 TextureCoordOut;
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif

#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif

#endif
uniform vec4 u_color; vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation) { float diffuse = max(dot(normalVector, lightDirection), 0.0); vec3 diffuseColor = lightColor * diffuse * attenuation; return diffuseColor; } void main(void) {
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    vec3 normal = normalize(v_normal);
#endif
    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i) { vec3 lightDirection = normalize(u_DirLightSourceDirection[i] * 2.0); combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0); }
#endif
    
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation); }
#endif
    
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i) { vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i]; float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0); vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]); vec3 spotLightDirection = normalize(u_SpotLightSourceDirection[i] * 2.0); float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection); attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos); attenuation = clamp(attenuation, 0.0, 1.0); combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation); }
#endif
    
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color * combinedColor;
#else
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
#endif
}
attribute vec4 a_position; attribute vec4 a_color; attribute vec2 a_texCoord; varying vec2 TextureCoordOut; varying vec4 ColorOut; void main() { ColorOut = a_color; TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; gl_Position = CC_PMatrix * a_position; }

#ifdef GL_ES
varying mediump vec4 ColorOut;
#else
varying vec4 ColorOut;
#endif
uniform vec4 u_color; void main(void) { gl_FragColor = ColorOut * u_color; }
attribute vec4 a_position; attribute vec4 a_color; attribute vec2 a_texCoord; varying vec2 TextureCoordOut; varying vec4 ColorOut; void main() { ColorOut = a_color; TextureCoordOut = a_texCoord; TextureCoordOut.y = 1.0 - TextureCoordOut.y; gl_Position = CC_PMatrix * a_position; }

#ifdef GL_ES
varying mediump vec2 TextureCoordOut; varying mediump vec4 ColorOut;
#else
varying vec4 ColorOut; varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color; void main(void) { gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * ColorOut * u_color; }
uniform mat4 u_cameraRot; attribute vec3 a_position; varying vec3 v_reflect; void main(void) { vec4 reflect = u_cameraRot * vec4(a_position, 1.0); v_reflect = reflect.xyz; gl_Position = vec4(a_position.xy, 1.0 , 1.0); }

#ifdef GL_ES
varying mediump vec3 v_reflect;
#else
varying vec3 v_reflect;
#endif
uniform samplerCube u_Env; uniform vec4 u_color; void main(void) { gl_FragColor = textureCube(u_Env, v_reflect) * u_color; }
attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec3 a_normal;
#ifdef GL_ES
varying mediump vec2 v_texCoord; varying mediump vec3 v_normal;
#else
varying vec2 v_texCoord; varying vec3 v_normal;
#endif
void main() { gl_Position = CC_MVPMatrix * a_position; v_texCoord = a_texCoord; v_normal = a_normal; }

#ifdef GL_ES
precision lowp float;
#endif
uniform vec3 u_color;
varying vec2 v_texCoord;
varying vec3 v_normal;
uniform int u_has_alpha;
uniform int u_has_light_map;
uniform sampler2D u_alphaMap;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform sampler2D u_lightMap;
uniform float u_detailSize[4];
uniform vec3 u_lightDir;
void main()
{
    vec4 lightColor;
    if(u_has_light_map<=0)
    {
        lightColor = vec4(1.0,1.0,1.0,1.0);
    }else
    {
        lightColor = texture2D(u_lightMap,v_texCoord);
    } float lightFactor = dot(-u_lightDir,v_normal);
    if(u_has_alpha<=0)
    {
        gl_FragColor = texture2D(u_texture0, v_texCoord)*lightColor*lightFactor;
    }else
    {
        vec4 blendFactor =texture2D(u_alphaMap,v_texCoord);
        vec4 color = vec4(0.0,0.0,0.0,0.0);
        color = texture2D(u_texture0, v_texCoord*u_detailSize[0])*blendFactor.r + texture2D(u_texture1, v_texCoord*u_detailSize[1])*blendFactor.g + texture2D(u_texture2, v_texCoord*u_detailSize[2])*blendFactor.b + texture2D(u_texture3, v_texCoord*u_detailSize[3])*(1.0 - blendFactor.a); gl_FragColor = vec4(color.rgb*lightColor.rgb*lightFactor, 1.0); } }
uniform float depth; attribute vec4 a_position; attribute vec2 a_texCoord; attribute vec3 a_color;
#ifdef GL_ES
varying mediump vec2 v_texCoord; varying mediump vec3 v_color;
#else
varying vec2 v_texCoord; varying vec3 v_color;
#endif
void main() { gl_Position = a_position; gl_Position.z = depth; gl_Position.w = 1.0; v_texCoord = a_texCoord; v_color = a_color; }

#ifdef GL_ES
varying mediump vec2 v_texCoord; varying mediump vec3 v_color;
#else
varying vec2 v_texCoord; varying vec3 v_color;
#endif
void main() { gl_FragColor = vec4(v_color, 1.0); }
2016-01-05 12:56:37.101 HelloWorldDemo-mobile[4307:1098722] cocos2d: surface size: 2208x1242
