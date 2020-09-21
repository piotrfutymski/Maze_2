#version 330

//Atrybuty
layout (location=0) in vec3 aVertex;
layout (location=1) in vec2 aTexCoords;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent; 

//Zmienne interpolowane

out vec2 texCoords;
out vec3 pos;
out vec3 tanViewPos;
out vec3 tanPos;

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 viewPos;

void main() 
{
    gl_Position = P * V * M * vec4(aVertex, 1.0);
    vec3 T = normalize(mat3(M) * aTangent);
    vec3 B = normalize(mat3(M) * aBitangent);
    vec3 N = normalize(mat3(M) * aNormal);
    mat3 TBN = transpose(mat3(T, B, N));

    texCoords = aTexCoords;
    pos = vec3(M * vec4(aVertex, 1.0));

    tanViewPos = TBN *  viewPos;
    tanPos = TBN * pos;
}
