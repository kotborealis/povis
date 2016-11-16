#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform bool lighting = false;
uniform sampler2D defaultTexture;
uniform sampler2D shadingTexture;

out vec4 fragColor;

#define PRECISION 0.0001

void main(){
    if(!lighting)
        fragColor = texture(defaultTexture, fragUV);
    else
        fragColor = texture(defaultTexture, fragUV) * texture(shadingTexture, fragUV);
}