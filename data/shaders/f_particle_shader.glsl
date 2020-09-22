#version 330 core

in vec2 input_texcoords;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;


void main()
{
    if(texture(tex, input_texcoords) != vec4(1.0,1.0,1.0,1.0))
        FragColor = color * texture(tex, input_texcoords);
    else
       discard;
}