#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;
in vec2 fragScreenPos;

uniform sampler2D diffuseTexture;
uniform vec3 color = vec3(1.f, 1.f, 1.f);
uniform uint tick;
uniform float inverse_ttl;

layout (location = 0) out vec4 fragColor;

void main(){
    float _ = 1 - float(tick) * inverse_ttl;
    float d = smoothstep(0.f, 1500.f, 1500.f - distance(fragLocalPos, fragScreenPos));
    fragColor = texture(diffuseTexture, fragUV) * vec4(1, 1, 1, d * _) * vec4(color, 1.f);
}