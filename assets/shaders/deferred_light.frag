#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

void main()
{
    FragColor = vec4(texture(gPosition, TexCoords).rgb,1.f);
}