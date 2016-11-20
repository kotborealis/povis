#version 330 core

#define pi 3.1415926535897932384626433832795

in vec2 fragUV;
in vec2 fragLocalPos;

uniform vec3 color = vec3(0, 0, 0);
uniform float step;

out vec4 fragColor;

void main(){
    fragColor = vec4(0, 0, 0, 1.f - step);
}