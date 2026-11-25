#version 410 core

layout(location = 0) in vec2 a_Position;

uniform mat4 u_Model;
uniform mat4 u_LightSpaceMatrix;

void main()
{
    gl_Position =
        u_LightSpaceMatrix *
        u_Model *
        vec4(a_Position, 0.0, 1.0);
}