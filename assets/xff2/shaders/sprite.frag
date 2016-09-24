#version 330 core

varying vec2 fragUV;
varying vec2 fragPos;

uniform sampler2D diffuseTexture;
uniform vec3 color;

out vec4 fragColor;

void main(){
    float d = smoothstep(0.f, 0.3f, 1.f - length(fragPos));
    vec4 _ = texture(diffuseTexture, fragUV) * vec4(color, d);
    if(_.a < 0.1)
        discard;
    else
        fragColor = _.rgba;
}