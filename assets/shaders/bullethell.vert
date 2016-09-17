#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
layout(location = 2) in float size;

uniform mat4 view;
uniform mat4 projection;

out vec2 bulletPosition;
out vec3 bulletColor;
out float bulletSize;

void main()
{
    gl_PointSize = size;
    gl_Position = projection * view * vec4(position, 0, 1.0f);

    bulletColor = color;
    bulletPosition = position;
    bulletSize = size;
}