#version 120

attribute vec3 position;
attribute vec3 normal;

uniform mat4 u_tModel;
uniform mat4 u_tView;
uniform mat4 u_tProj;

const int FOG_TYPE_LINEAR     = 0;
const int FOG_TYPE_EXP        = 1;
const int FOG_TYPE_EXP_SQUARE = 2;

struct LFog
{
    int type;
    vec4 color;
    float density;

    float start;
    float end;

    int isActive;
};


uniform LFog u_fog;

varying vec3 vNormal;
varying vec3 vFragPos;
varying float vVisibility;

void main()
{
    gl_Position = u_tProj * u_tView * u_tModel * vec4( position, 1.0f );
    vFragPos = vec3( u_tModel * vec4( position, 1.0f ) );
    vNormal = mat3( u_tModel ) * normal;

    vec4 _posRespectToCamera = u_tView * u_tModel * vec4( position, 1.0f );
    float _distToCamera = length( _posRespectToCamera.xyz );

    if ( u_fog.isActive == 1 )
    {
        if ( u_fog.type == FOG_TYPE_LINEAR )
        {
            vVisibility = 1 - ( _distToCamera - u_fog.start ) / ( u_fog.end - u_fog.start );
        }
        else if ( u_fog.type == FOG_TYPE_EXP )
        {
            vVisibility = exp( -( _distToCamera - u_fog.start ) * u_fog.density );
        }
        else if ( u_fog.type == FOG_TYPE_EXP_SQUARE )
        {
            vVisibility = exp( -pow( ( _distToCamera - u_fog.start ) * u_fog.density, 2 ) );
        }

        vVisibility = clamp( vVisibility, 0.0f, 1.0f );
    }
    else
    {
        vVisibility = 1.0f;
    }
}