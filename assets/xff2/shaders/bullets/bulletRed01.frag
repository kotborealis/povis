#version 330 core

in vec2 fragUV;
in vec2 fragPos;

uniform sampler2D diffuseTexture;
uniform vec3 color = vec3(1.f, 1.f, 1.f);
uniform uint tick;
uniform uint ttl;

out vec4 fragColor;

void main(){
    float _ = 1 - float(tick)/float(ttl);
    fragColor = texture(diffuseTexture, fragUV) * vec4(1.f, 1.f, 1.f, _) * vec4(color, 1.f);
}