attribute vec3 pos;     
attribute vec4 color;   

uniform mat4 M;         
uniform mat4 V;         
uniform mat4 P;         

varying vec4 v_color;   
void main()
{
    v_color=color;
    gl_position=P*V*M*vec4(pos,1.0);  
}