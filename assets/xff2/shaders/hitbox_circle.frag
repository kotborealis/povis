#version 330 core

#define pi 3.1415926535897932384626433832795

in vec2 fragUV;
in vec2 fragLocalPos;

out vec4 fragColor;

float arc(vec2 pos, float radius1, float radius2){
	vec2 b = fragLocalPos;
    float angdist = mod(atan(b.x, b.y), 2.0*pi);
	return ((angdist < pi * 2)
                    && (length(b) >= radius1)
                    && (length(b) <= radius2) ? 1.0 : 0.0);
}

void main(){
	fragColor = vec4(1.f, 0.f, 0.5f, 1.f) * arc(fragLocalPos, 0.95f, 1.f);
}