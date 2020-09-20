#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "shaderProgram.h"
#include "environment.h"

class Entity
{
public:

	Entity(ShaderProgram* program);

	virtual void draw() = 0;

	virtual void update(float dt) = 0;

protected:

	ShaderProgram * _shaderProgram;

};