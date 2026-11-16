#version 410 core

out vec4 FragColor;

uniform float time;

void main(){
    FragColor = vec4(time, 0.0, 1.0, 1.0);
}