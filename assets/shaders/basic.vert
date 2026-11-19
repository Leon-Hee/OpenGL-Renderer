#version 410 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 TexCoords;

void main(){
    //gl_Position = u_Projection * u_View * vec4(a_Position, 0.0, 1.0);
    gl_Position = vec4(a_Position, 0.0, 1.0);
    TexCoords = a_TexCoords;
}