#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform sampler2D diffuseTexture;
uniform vec3 color = vec3(1.f, 1.f, 1.f);

uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;

struct Light {
    mat4 model;
    vec2 color;
    float linear;
};

const int MAX_LIGHTS = 32;
uniform Light lights[MAX_LIGHTS];
uniform int actual_lights;

void main(){
    vec4 diffuse = texture(diffuseTexture, fragUV);
    float alpha = 0.2f;
    for(int i = 0; i < MAX_LIGHTS; i++){
        vec4 pos = projection * view * lights[i].model * vec4(fragLocalPos.x, fragLocalPos.y, 0, 1) / 1000;  //1000 is Camera Z pos
        float distance = distance(pos.xy, fragLocalPos);
        alpha += (1.f - min(distance/lights[i].linear, 1.0)) * 0.5f;
    }
    fragColor = diffuse * alpha * vec4(color, 1);
}