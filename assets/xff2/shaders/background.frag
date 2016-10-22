#version 330 core

in vec2 fragUV;
in vec2 fragPos;

uniform sampler2D diffuseTexture;
uniform vec3 color;

out vec4 fragColor;

void main(){
    float d = smoothstep(0.f, 0.5f, 1.f - length(fragPos));
    vec4 _ = texture(diffuseTexture, fragUV) * vec4(color, d);
    fragColor = _.rgba;
}