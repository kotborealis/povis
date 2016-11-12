#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D defaultTexture;
uniform sampler2D shadingTexture;
uniform sampler2D uiTexture;

out vec4 fragColor;

void main(){
    fragColor = vec4(texture(defaultTexture, fragUV) /** texture(shadingTexture, fragUV)*/ + texture(uiTexture, fragUV));
}