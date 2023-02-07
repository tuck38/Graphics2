#version 450                          
layout (location = 0) in vec3 vPos;  
layout (location = 1) in vec3 vNormal;

out vec3 Normal;
uniform mat4 _CamView;
uniform mat4 _CamProj;
uniform mat4 _Cube;

void main(){ 
    Normal = vNormal;
    gl_Position =   _CamProj * _CamView  * _Cube * vec4(vPos, 1);
}
