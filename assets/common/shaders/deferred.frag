#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform bool lighting = false;
uniform sampler2D defaultTexture;
uniform sampler2D uiTexture;

out vec4 fragColor;

#define PRECISION 0.0001

void main(){
    vec4 texel_default = texture(defaultTexture, fragUV);
    vec4 texel_ui = texture(uiTexture, fragUV);

    vec4 texel = texel_default;
    texel = mix(texel, texel_ui, texel_ui.a);

    fragColor = texel;
}