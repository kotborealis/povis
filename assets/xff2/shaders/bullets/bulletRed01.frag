#version 330 core

varying vec2 fragUV;
varying vec2 fragPos;

uniform sampler2D diffuseTexture;
uniform vec3 color;

out vec4 fragColor;

void main(){
    vec4 _ = texture(diffuseTexture, fragUV) * vec4(color, 1);
    if(_.a < 0.1)
        discard;
    else
        fragColor = _.rgba;
}