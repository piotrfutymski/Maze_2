#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>


class ShaderProgram
{
public:

	ShaderProgram(const char* vertex_file_path, const char* fragment_file_path);

	GLuint getID()const;


private:

	GLuint _shaderProgramID;

};