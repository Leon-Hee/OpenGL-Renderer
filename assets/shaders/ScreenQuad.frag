#version 410 core

in vec2 TexCoords;

uniform sampler2D screenTexture;

out vec4 FragColor;

void main()
{
    vec4 color = texture(screenTexture, TexCoords);
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    FragColor = vec4(vec3(gray), 1.0);
}