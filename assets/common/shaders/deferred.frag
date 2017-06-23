#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform bool lighting = false;
uniform sampler2D defaultTexture;

out vec4 fragColor;

#define PRECISION 0.0001

void main(){
    fragColor = texture(defaultTexture, fragUV);
}