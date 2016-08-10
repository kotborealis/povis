#version 330 core

out vec4 color;
in vec2 TexCoord;
in vec3 t_color;

uniform sampler2D m_texture;

void main(){
	color = texture(m_texture, TexCoord) * vec4(t_color, 1);
}