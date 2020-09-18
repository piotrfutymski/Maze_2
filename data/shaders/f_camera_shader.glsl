#version 330

in vec2 input_texcoords;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

uniform sampler2D tex;

void main()
{ 
    if(texture(tex, input_texcoords) != (1.0,1.0,1.0,1.0))
        pixelColor = vec4(1.0, 1.0, 1.0, 0.5)* texture(tex, input_texcoords);
    else
        pixelColor = vec4(0.0, 0.0, 0.0, 0.0);
}  