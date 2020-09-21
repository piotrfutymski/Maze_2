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
    pos = vec3(M * vec4(aVertex, 1.0));
    gl_Position = P * V * vec4(pos, 1.0);

    vec3 T = normalize(vec3(M * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(M * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(M * vec4(aNormal, 0.0)));
    mat3 TBN = transpose(mat3(T, B, N));

    texCoords = aTexCoords;

    tanViewPos = TBN * viewPos;
    tanPos = TBN * pos;
}
