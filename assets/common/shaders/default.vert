#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 UV;

out vec2 fragUV;
out vec2 fragLocalPos;

void main(){
	gl_Position = vec4(position, 1.0f);

    fragUV = UV;
    fragLocalPos = position.xy;
}