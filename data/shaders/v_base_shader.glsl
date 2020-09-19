#version 330

struct LIGHT
{
    vec3 pos;
    vec3 color;
};

//Atrybuty
layout (location=0) in vec3 aVertex;
layout (location=1) in vec2 aTexCoords;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent; 

//Zmienne interpolowane
out struct INTER
{
vec2 texCoords;
vec3 pos;
vec3 tanViewPos;
vec3 tanPos;
int lightCount;
LIGHT tanLights[64];
} inter;

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform LIGHT lights[8];
uniform int lightCount;
uniform vec3 viewPos;

void main() 
{
    gl_Position = P * V * M * vec4(aVertex, 1.0);

    vec3 T = normalize(vec3(M * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(M * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(M * vec4(aNormal, 0.0)));
    mat3 TBN = transpose(mat3(T, B, N));

    inter.texCoords = aTexCoords;
    inter.pos = vec3(M * vec4(aVertex, 0.0));

    inter.lightCount = lightCount;
    for(int i = 0; i < lightCount ; i++)
    {
        inter.tanLights[i].pos = TBN * lights[i].pos;
        inter.tanLights[i].color = lights[i].color;
    }

    inter.tanViewPos = TBN * viewPos;
    inter.tanPos = TBN * vec3(M * vec4(aVertex, 0.0));
}
