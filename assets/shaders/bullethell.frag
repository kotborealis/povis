#version 330 core

in vec3 bulletColor;

out vec4 outColor;

void main()
{
    outColor = vec4(bulletColor, 1.0f);
}