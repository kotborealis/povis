#version 330 core

in vec2 fragUV;

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