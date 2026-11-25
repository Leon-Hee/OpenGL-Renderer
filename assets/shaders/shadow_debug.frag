#version 410 core

out vec4 FragColor;

uniform sampler2D u_DepthMap;

in vec2 v_TexCoord;

void main()
{
    float depth = texture(u_DepthMap, v_TexCoord).r;

    FragColor = vec4(
        depth,
        depth,
        depth,
        1.0
    );
}