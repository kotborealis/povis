#version 330 core

in vec2 bulletPosition;
in vec3 bulletColor;
in float bulletSize;

out vec4 outColor;

void main(){
    gl_FragColor = vec4(bulletColor, 1);
}