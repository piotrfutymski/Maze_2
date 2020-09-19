#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "shaderProgram.h"
#include "entity.h"
#include <vector>
#include <memory>
#include "immobileObject.h"
#include "camera.h"

class Maze
{
public:

	int play();

private:

	bool init();
	//
	bool initGLFW();
	bool initGlew();
	bool initWindow();

	bool loadShaders();
	bool loadObjects();

	void processInput();
	void renderWindow();
	void poolEvents();

private:

	GLFWwindow* _window;

	std::vector<std::unique_ptr<Entity>> _entities;

	Camera* _camera;

	std::vector<Model> _models;
	std::vector<Texture> _textures;
	std::vector<ShaderProgram> _shaders;

};
