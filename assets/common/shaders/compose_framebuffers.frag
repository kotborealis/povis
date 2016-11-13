#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D defaultTexture;
uniform sampler2D shadingTexture;
uniform sampler2D uiTexture;

out vec4 fragColor;

#define PRECISION 0.0001

void main(){
    vec4 default_t = texture(defaultTexture, fragUV);
    vec4 shading_t = texture(shadingTexture, fragUV);
    vec4 ui_t = texture(uiTexture, fragUV);

    if(ui_t.x > PRECISION || ui_t.y > PRECISION || ui_t.z > PRECISION){
        fragColor = ui_t;
    }
    else{
        fragColor = default_t;
    }
}