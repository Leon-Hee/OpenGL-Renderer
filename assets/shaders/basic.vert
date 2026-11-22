#version 410 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

out vec2 TexCoords;

void main(){
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 0.0, 1.0);

    TexCoords = a_TexCoords;
}