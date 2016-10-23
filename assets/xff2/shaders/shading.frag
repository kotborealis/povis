#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D diffuseTexture;
uniform vec3 color = vec3(1.f, 1.f, 1.f);

out vec4 fragColor;

void main(){
    fragColor = texture(diffuseTexture, fragUV) * vec4(color, 1);
}