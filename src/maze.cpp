#include "maze.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		Environment::F_Pressed = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		Environment::F_Pressed = true;
}

int Maze::play()
{
	srand(time(NULL));
	if (this->init() == false)
		return -1;

	glfwSetTime(0);

	while (!glfwWindowShouldClose(_window))
	{
		this->processInput();
		this->shadow();
		this->renderWindow();
		Environment::F_Pressed = false;
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
	glfwSetKeyCallback(_window, key_callback);
	glfwSetMouseButtonCallback(_window, mouse_button_callback);

	Environment::window = _window;
	Environment::windowWidth = 1024;
	Environment::windowHeight = 768;


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
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //W³¹cz test g³êbokoœci na pikselach
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

void Maze::shadow()
{
	glViewport(0, 0, Environment::smapWidth, Environment::smapHeight); //change res
	glBindFramebuffer(GL_FRAMEBUFFER, Environment::depthMapFBO);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	for (int i = 0; i < Environment::lightsCount; i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Environment::lights[i].depthMap , 0); //attach depth texture to depth FBO depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);
		for (auto& entity : _entities)
			entity->shadow(Environment::lights[i].lightSpaceMatrix);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); //reset framebuffer to default
	glViewport(0, 0, Environment::windowWidth, Environment::windowHeight); //reset viewport
}

void Maze::renderWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& entity : _entities)
		entity->draw();

	glfwSwapBuffers(_window);
}

