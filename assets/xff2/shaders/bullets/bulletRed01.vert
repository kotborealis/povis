#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragUV;
out vec2 fragLocalPos;
out vec2 fragScreenPos;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f);

    fragUV = UV;
    fragLocalPos = position.xy;
    fragScreenPos = gl_Position.xy;
}