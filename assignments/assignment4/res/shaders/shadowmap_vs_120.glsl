#version 120

attribute vec3 position;

uniform mat4 u_tModel;
uniform mat4 u_tView;
uniform mat4 u_tProj;

void main()
{
    gl_Position = u_tProj * u_tView * u_tModel * vec4( position, 1.0f );
}