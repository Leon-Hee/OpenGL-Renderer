#version 410 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in vec3 a_Tangent;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 WorldPosition;

void main()
{
    gl_Position =
        u_Projection *
        u_View *
        u_Model *
        vec4(a_Position, 0.0, 1.0);

    mat3 normalMatrix =
        transpose(inverse(mat3(u_Model)));

    Normal =
        normalize(normalMatrix * a_Normal);

    Tangent =
        normalize(mat3(u_Model) * a_Tangent);

    TexCoords =
        a_TexCoords;

    WorldPosition =
        vec3(u_Model * vec4(a_Position, 0.0, 1.0));
}