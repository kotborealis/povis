#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform vec3 color = vec3(1.f, 1.f, 1.f);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;

struct Light {
    vec2 pos;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

const int MAX_LIGHTS = 32;
uniform Light lights[MAX_LIGHTS];
uniform int actual_lights;

void main(){
    float lighting = 0.f;
    for(int i = 0; i < actual_lights; i++){
        vec2 l_pos = lights[i].pos;
        float d = distance(l_pos/1000, fragLocalPos);
        float att = 1.f / (lights[i].constant + lights[i].linear * d + lights[i].quadratic * d * d);
        lighting += att;
    }
    fragColor = vec4(vec3(1, 1, 1) * lighting, 1);
}