#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int width;
uniform int height;
uniform float inv_width;
uniform float inv_height;
uniform int cur;

out vec2 fragUV;
out vec2 fragLocalPos;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f);

    vec2 sprite_uv = vec2(inv_width, inv_height);
    fragUV = UV * sprite_uv + sprite_uv * vec2(mod(cur, width), int(cur)/int(width));
    fragLocalPos = position.xy;
}