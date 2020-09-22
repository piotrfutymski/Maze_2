#version 330

//Atrybuty
layout (location=0) in vec3 aVertex;
layout (location=1) in vec2 aTexCoords;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent; 

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec2 input_texcoords;

void main() 
{
	input_texcoords = aTexCoords;
	gl_Position = P * V * M * vec4(aVertex, 1.0);
}
