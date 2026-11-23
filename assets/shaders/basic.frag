#version 410 core

in vec2 TexCoords;
out vec4 FragColor;

uniform float u_Value;
uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main(){
    FragColor = texture(u_Texture, TexCoords);

}