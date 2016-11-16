#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D defaultTexture;
uniform sampler2D uiTexture;

out vec4 fragColor;

void main(){
    vec4 texel = texture(defaultTexture, fragUV);
    vec4 texel_ui = texture(uiTexture, fragUV);
    fragColor = mix(texel, texel_ui, texel_ui.a);
}