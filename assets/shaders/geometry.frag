#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;

uniform sampler2D diffuseTexture;

void main()
{
    gPosition = FragPos;
    gAlbedoSpec.rgb = texture(diffuseTexture, TexCoords).rgb;
}