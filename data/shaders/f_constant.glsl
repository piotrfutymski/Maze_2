#version 330


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela


uniform vec4 color=vec4(1,0,0,1);

void main(void) {
	pixelColor=color;
}
