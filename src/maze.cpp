#include "maze.h"

int Maze::play()
{
	if (this->init() == false)
		return -1;

	glfwSetTime(0);

	while (!glfwWindowShouldClose(_window))
	{
		this->processInput();
		this->renderWindow();
		this->poolEvents();
	}

	glfwTerminate();
	return 0;
}

bool Maze::init()
{
	auto res = this->initGLFW();
	res &= this->initWindow();
	res &= this->initGlew();
	res &= this->loadShaders();
	res &= this->loadObjects();
	return res;
}

bool Maze::initGLFW()
{
	glewExperimental = true;
	if (glfwInit() == GLFW_FALSE)
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	return true;
	
}

bool Maze::initGlew()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		return false;

	return true;
	
}

bool Maze::initWindow()
{
	_window = glfwCreateWindow(1024, 768, "Maze 2", NULL, NULL);
	if (_window == NULL)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	return true;

}

bool Maze::loadShaders()
{
	_shaders.emplace_back("data/shaders/v_constant.glsl", "data/shaders/f_constant.glsl");
	return true;
}

bool Maze::loadObjects()
{
	_entities.push_back(std::move(std::make_unique<TestEntity>(_shaders[0], 0)));
	_entities.push_back(std::move(std::make_unique<TestEntity>(_shaders[0], 1)));
	return true;
}

void Maze::processInput()
{
}

void Maze::renderWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& entity : _entities)
		entity->draw();

	glfwSwapBuffers(_window);
}

void Maze::poolEvents()
{
	glfwPollEvents();
}
