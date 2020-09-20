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
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

bool Maze::init()
{
	auto res = this->initGLFW();
	res &= this->initWindow();
	res &= this->initGlew();
	res &= this->initOpenGL();

	Environment::init("data/height_map.txt");
	_factory.init();
	_factory.load("data/world.txt", _entities);

	return res;
}

bool Maze::initGLFW()
{
	if (glfwInit() == GLFW_FALSE)
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
	glfwSwapInterval(1);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Environment::window = _window;

	return true;
}

bool Maze::initGlew()
{
	if (glewInit() != GLEW_OK)
		return false;

	return true;
}

bool Maze::initOpenGL()
{
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolor�w
	glEnable(GL_DEPTH_TEST); //W��cz test g��boko�ci na pikselach
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}


void Maze::processInput()
{
	for (auto& entity : _entities)
		entity->update(glfwGetTime());

	glfwSetTime(0); 
}

void Maze::renderWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& entity : _entities)
		entity->draw();

	glfwSwapBuffers(_window);
}

