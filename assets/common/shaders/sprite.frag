#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;
in vec2 fragScreenPos;

uniform sampler2D diffuseTexture;

out vec4 fragColor;

void main(){
    fragColor = texture(diffuseTexture, fragUV);
}