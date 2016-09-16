#version 330 core

in vec2 fragUV;

uniform sampler2D diffuseTexture;

out vec4 fragColor;

void main(){
    vec4 _ = texture(diffuseTexture, fragUV);
    if(_.a < 0.1)
        discard;
    else
	    fragColor = _.rgba;
}