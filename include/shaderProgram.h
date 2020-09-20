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

	GLuint get()const;

	GLuint u(const char* variableName);
	GLuint a(const char* variableName); 

private:

	GLuint _shaderProgramID;

};