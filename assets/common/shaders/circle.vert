#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in float radius;
layout(location = 2) in vec3 color;
layout(location = 3) in float segments;

out vec2 vRadius;
out vec3 vColor;
out float vSegments;

uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = view * projection * vec4(pos, 1.0);
    vColor = color;
    vSegments = segments;
    vRadius = (view * projection * vec4(radius, radius, 0, 1)).xy;
}