#version 330

//Atrybuty
layout (location=0) in vec3 aVertex;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main() 
{
	gl_Position = P * V * M * vec4(aVertex, 1.0);
}
