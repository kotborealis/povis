#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec3 color;

out vec2 vSize;
out vec3 vColor;

uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = view * projection * vec4(pos, 1.0);
    vColor = color;

    vSize.x = (view * projection * vec4(size.x, 0, 0, 1)).x;
    vSize.y = (view * projection * vec4(0, size.y, 0, 1)).y;
}