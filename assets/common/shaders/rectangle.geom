#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 5) out;

in vec3 vColor[];
in vec2 vSize[];

out vec3 fColor;

void main(){
    fColor = vColor[0];

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(vSize[0].x, 0, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(vSize[0].x, vSize[0].y, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0, vSize[0].y, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
}