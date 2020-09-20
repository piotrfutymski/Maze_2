#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "lodepng.h"

class Texture
{
public:

	Texture(const char* filename);

	GLuint get()const;

private:
	GLuint id;

};