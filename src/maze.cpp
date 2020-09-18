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
	if (glfwInit() == GLFW_FALSE)
		return false;

	return true;
	
}

bool Maze::initGlew()
{
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
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	return true;

}

bool Maze::loadShaders()
{
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //W³¹cz test g³êbokoœci na pikselach
	_shaders.emplace_back("data/shaders/v_base_shader.glsl", "data/shaders/f_base_shader.glsl");
	return true;
}

bool Maze::loadObjects()
{
	
	_textures.emplace_back("data/textures/wall.png");
	Model tmp;
	tmp.loadMesh("data/models/wall.obj");
	_models.push_back(std::move(tmp));
	_entities.push_back(std::move(std::make_unique<ImmobileObject>(_shaders[0], _models[0], _textures[0])));
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
