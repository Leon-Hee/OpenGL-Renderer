#version 410 core

in vec2 TexCoords;
out vec4 FragColor;

uniform float u_Value;
uniform sampler2D u_Texture;

void main(){
    FragColor = texture(u_Texture, TexCoords);
    FragColor *= u_Value;
}