#version 330 core

in vec2 texture_coord;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 color;

void main(){
	color = texture(diffuse, -texture_coord);
}