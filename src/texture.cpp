#include "..\include\texture.h"


Texture::Texture(const char* filename, int shiny, float parallaxScale)
    : shininess(shiny), parallaxStrength(parallaxScale)
{
    //Wczytanie do pamiêci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamiêci karty graficznej
    glGenTextures(1, &id); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, id); //Uaktywnij uchwyt

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
}


GLuint Texture::get() const
{
	return id;
}
