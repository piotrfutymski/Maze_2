#version 330

out vec4 fragColor;

struct LIGHT
{
    vec3 pos;
    vec3 color;
};

in vec2 texCoords;
in vec3 pos;
in vec3 tanViewPos;
in vec3 tanPos;
in mat3 TBN;

uniform sampler2D diffuseMap;
uniform sampler2D heightMap;
uniform sampler2D normalMap;


void main()
{
    vec3 viewDirection = normalize(tanViewPos - tanPos);
    float height =  texture(heightMap, texCoords).r;    
    vec2 offset = viewDirection.xy / viewDirection.z * (height * 0.5);
    vec2 newTexCoords = texCoords + offset;  

    if(newTexCoords.x > 1.0 || newTexCoords.y > 1.0 || newTexCoords.x < 0.0 || newTexCoords.y < 0.0)
    discard;

    vec3 color = texture(diffuseMap, newTexCoords).rgb;
    vec3 normal = texture(normalMap, newTexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0); //convert [0,1] space to [-1,1]
    
    /*vec3 phongLight = vec3(0.1, 0.1, 0.1)*5; //ambient
    for(int i = 0; i < inter.lightCount; i++)
    {
        vec3 lightDirection = normalize(inter.tanLights[i].pos - inter.tanPos);  
        vec3 reflectDirection = reflect(-lightDirection, normal);

        float dist = distance(inter.tanPos, inter.tanLights[i].pos);
        float t_distance = (1 / dist) * (1 / dist);
    
        float diff = max(dot(normal, lightDirection), 0.0);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);   //32 -> material shininess
    
        vec3 diffuse = inter.tanLights[i].color * diff * t_distance;
        vec3 specular = spec * inter.tanLights[i].color / dist;

        phongLight += (diffuse + specular);
        
     }
     phongLight.rgb = vec3(min(phongLight.r,1.0), min(phongLight.g,1.0), min(phongLight.b,1.0));*/
     fragColor = vec4(color, 1.0);
}  