#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "shaderProgram.h"
#include "modelFactory.h"
#include <vector>
#include <memory>
#include <map>
#include "immobileObject.h"
#include "camera.h"

class Maze
{
public:

	Maze() :_factory(_entities) {};

	int play();

private:

	bool init();
	//
	bool initGLFW();
	bool initGlew();
	bool initWindow();
	bool initOpenGL();

	void buildObjects();

	void processInput();
	void renderWindow();
	void poolEvents();

private:

	GLFWwindow* _window;

	std::vector<std::unique_ptr<Entity>> _entities;
	Camera* _camera;
	
	ModelFactory _factory;

};
