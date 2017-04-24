#version 120
attribute vec3 pos;
attribute vec3 normal;
attribute vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

varying vec3 _normal;
varying vec2 _texcoord;
void main()
{
    _texcoord = texcoord;
    _normal = mat3(NM)*normal;
    gl_Position = P * V * M * vec4(pos,1.0);
}