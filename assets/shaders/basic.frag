#version 330 core

in vec2 texture_coord;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

out vec4 color;

void main(){
	color = texture(diffuseTexture, -texture_coord);
}