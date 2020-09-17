﻿#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
layout (location=0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec3 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wspó³rzêdne teksturowania


//Zmienne interpolowane
out vec2 input_texcoords;
out vec3 input_normal;
out vec3 input_coords;


void main() 
{
    input_normal = normal;
    input_texcoords = texCoord;
    input_coords = vec3(M * vec4(vertex, 1.0));
    gl_Position = P * V * M * vec4(vertex, 1.0);
}
