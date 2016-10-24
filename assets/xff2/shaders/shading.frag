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
    vec3 color;
    float inverse_linear;
};

const int MAX_LIGHTS = 32;
uniform Light lights[MAX_LIGHTS];
uniform int actual_lights;

void main(){
    vec4 diffuse = texture(diffuseTexture, fragUV);
    float lighting = 0.1f;
    vec3 lighting_color = vec3(0, 0, 0);
    for(int i = 0; i < actual_lights; i++){
        vec4 pos = projection * view * lights[i].model * vec4(fragLocalPos.x, fragLocalPos.y, 0, 1) / 1000;  //1000 is Camera Z pos
        float distance = distance(pos.xy, fragLocalPos);
        float _ = (1.f - min(distance*lights[i].inverse_linear, 1.f)) * 0.5f;
        lighting += _; //lights inverse_linear should be 1/linear (for better performance)
        lighting_color += lights[i].color * _;
    }
    fragColor = diffuse * lighting * vec4(color * lighting_color, 1);
}