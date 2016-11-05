#version 330 core

in vec2 fragUV;
in vec2 fragLocalPos;

uniform vec3 color = vec3(1.f, 1.f, 1.f);

uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;

struct Light {
    mat4 model;
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
    vec3 lighting_color = vec3(1.f, 1.f, 1.f);
    for(int i = 0; i < actual_lights; i++){
        vec4 pos = projection * view * lights[i].model * vec4(fragLocalPos.x, fragLocalPos.y, 0, 1) / 1000;  //1000 is Camera Z pos
        float distance = distance(pos.xy, fragLocalPos);
        float att = 1.f / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
        lighting += att;
        //lighting_color += lights[i].color * att;
    }
    fragColor = lighting * vec4(color * lighting_color, 1);
}