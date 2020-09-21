#version 330

out vec4 fragColor;

in vec2 texCoords;
in vec3 tanViewPos;
in vec3 tanPos;
in mat3 TBN;

uniform sampler2D diffuseMap;
uniform sampler2D heightMap;
uniform sampler2D normalMap;

uniform vec3 lightPos[8];
uniform vec3 lightColors[8];
uniform int lightCount;

void main()
{
    vec3 viewDirection = normalize(tanViewPos-tanPos);
    float depth = 1- texture(heightMap, texCoords).r;
    vec2 offset = viewDirection.xy * (depth*0.1);
    vec2 shiftedTexCoords = texCoords ; //no parallax atm 

    if(shiftedTexCoords.x > 1.0 || shiftedTexCoords.y > 1.0 || shiftedTexCoords.x < 0.0 || shiftedTexCoords.y < 0.0)
    discard;

    vec3 color = texture(diffuseMap, shiftedTexCoords).rgb;
    vec3 normal = texture(normalMap, shiftedTexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    vec3 phongLight = vec3(0.1, 0.1, 0.1);
    for(int i = 0; i < lightCount; i++)
    {
        vec3 tanLightPos = TBN*lightPos[i];
        vec3 lightDirection = normalize(tanLightPos - tanPos);  
        vec3 reflectDirection = reflect(-lightDirection, normal);

        float dist = distance(tanPos, tanLightPos);
        float t_distance = (1 / dist) * (1 / dist);
    
        float diff = max(dot(normal, lightDirection), 0.0);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 2);
    
        vec3 diffuse = lightColors[i] * diff * t_distance;
        vec3 specular = spec * lightColors[i] / dist;

        phongLight += (diffuse + specular);
        
     }

     fragColor = vec4(phongLight*color, 1.0);
}  