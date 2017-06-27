#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec3 color;
layout(location = 3) in float thickness;

out vec2 vSize;
out vec3 vColor;
out vec4 vThicknessX;
out vec4 vThicknessY;

uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = view * projection * vec4(pos, 1.0);
    vColor = color;

    vSize.x = (view * projection * vec4(size.x, 0, 0, 0)).x;
    vSize.y = (view * projection * vec4(0, size.y, 0, 0)).y;

    vThicknessX = (view * projection * vec4(thickness, 0, 0, 0));
    vThicknessY = (view * projection * vec4(0, thickness, 0, 0));
}