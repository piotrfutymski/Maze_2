#version 330

//Atrybuty
layout (location=0) in vec2 vertex;
layout (location=1) in vec2 texCoord;


//Zmienne interpolowane
out vec2 input_texcoords;

void main() 
{
    input_texcoords = texCoord;
    gl_Position = vec4(vertex, -1.0, 1.0);
}
