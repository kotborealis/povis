#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 32) out;

in vec3 vColor[];
in vec2 vSize[];
in vec4 vThicknessX[];
in vec4 vThicknessY[];

out vec3 fColor;

void Emit(vec4 v){
    gl_Position = v;
    EmitVertex();
}

void main(){
    fColor = vColor[0];

    vec4 bl = gl_in[0].gl_Position;;
    vec4 br = gl_in[0].gl_Position + vec4(vSize[0].x, 0, 0, 0);
    vec4 tr = gl_in[0].gl_Position + vec4(vSize[0].x, vSize[0].y, 0, 0);
    vec4 tl = gl_in[0].gl_Position + vec4(0, vSize[0].y, 0, 0);

//    Emit(tl); Emit(tr); Emit(br); Emit(bl); Emit(tl);

    //top
    Emit(tl);
    Emit(tr);
    Emit(tl - vThicknessY[0]);
    EndPrimitive();

    Emit(tl - vThicknessY[0]);
    Emit(tr - vThicknessY[0]);
    Emit(tr);
    EndPrimitive();

    //left
    Emit(tl);
    Emit(tl + vThicknessX[0]);
    Emit(bl);
    EndPrimitive();

    Emit(bl + vThicknessX[0]);
    Emit(tl + vThicknessX[0]);
    Emit(bl);
    EndPrimitive();

    //bottom
    Emit(bl);
    Emit(br);
    Emit(bl + vThicknessY[0]);
    EndPrimitive();

    Emit(bl + vThicknessY[0]);
    Emit(br + vThicknessY[0]);
    Emit(br);
    EndPrimitive();

    //right
    Emit(tr);
    Emit(tr - vThicknessX[0]);
    Emit(br);
    EndPrimitive();

    Emit(br - vThicknessX[0]);
    Emit(tr - vThicknessX[0]);
    Emit(br);
    EndPrimitive();

//    gl_Position = gl_in[0].gl_Position;
//    EmitVertex();
//
//    gl_Position = gl_in[0].gl_Position + vec4(vSize[0].x, 0, 0, 0);
//    EmitVertex();
//
//    gl_Position = gl_in[0].gl_Position + vec4(vSize[0].x, vSize[0].y, 0, 0);
//    EmitVertex();
//
//    gl_Position = gl_in[0].gl_Position + vec4(0, vSize[0].y, 0, 0);
//    EmitVertex();
//
//    gl_Position = gl_in[0].gl_Position;
//    EmitVertex();

    EndPrimitive();
}