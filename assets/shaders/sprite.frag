#version 330 core

in vec2 fragUV;

uniform sampler2D diffuseTexture;

out vec4 fragColor;

void main(){
	fragColor = texture(diffuseTexture, fragUV);
}