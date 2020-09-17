#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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

};
