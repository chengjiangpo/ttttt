#version 120
attribute vec3 pos;
attribute vec2 texcoord;
attribute vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

varying vec3 v_normal;
varying vec2 v_texcoord;
void main()
{
    v_normal = mat3(NM)*normal;
    v_texcoord = texcoord;
    gl_Position = P * V * M * vec4(pos,1.0);
}