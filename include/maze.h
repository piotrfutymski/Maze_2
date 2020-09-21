#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "shaderProgram.h"
#include "worldGenerator.h"
#include <vector>
#include <memory>
#include <map>
#include "object.h"
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
	bool initOpenGL();

	void processInput();
	void shadow();
	void renderWindow();

private:

	GLFWwindow* _window;

	std::vector<std::unique_ptr<Entity>> _entities;
	
	WorldGenerator _factory;

};
