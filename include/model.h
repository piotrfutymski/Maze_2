#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model
{
public:

	Model();

	Model(std::string objPath);

	GLuint get() const;

	GLsizei count() const;

private:

	void processFace(std::string& line, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn);

	void addTriangle(int off1, int off2, int off3, const glm::vec3* pos, const glm::vec2* uv, const glm::vec3* nm);

	void sendToGpu();

private:

	GLuint VBO, VAO;
	const static int vertexAttrSize = 14;

	std::vector<GLfloat> _mesh;
};