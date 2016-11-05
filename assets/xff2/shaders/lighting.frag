#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D diffuseTexture;
uniform sampler2D shadingTexture;
out vec4 fragColor;

void main(){

    fragColor = vec4(texture(diffuseTexture, fragUV) * texture(shadingTexture, fragUV));
}