#version 330

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu


void main(void) {
    gl_Position=vertex;
}
