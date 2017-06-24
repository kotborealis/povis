#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 128) out;

in vec3 vColor[];
in vec2 vRadius[];
in float vSegments[];

out vec3 fColor;

const float PI = 3.14159265358979323846264;

void main(){
    fColor = vColor[0];

    for(float i = 0; i <= vSegments[0]; i++){
        float ang = PI * 2 / vSegments[0] * i;

        vec4 offset = vec4(vRadius[0].x * cos(ang), vRadius[0].y * -sin(ang), 0, 0);
        gl_Position = gl_in[0].gl_Position + offset;
        EmitVertex();
    }

    EndPrimitive();
}