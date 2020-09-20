#include "maze.h"

/*void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	

}*/

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
	res &= this->initOpenGL();
	_factory.init();
	this->buildObjects();

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
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetKeyCallback(_window, key_callback);

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


void Maze::buildObjects()
{
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 tmpM(1.0f);
		tmpM = glm::translate(tmpM, glm::vec3(1.0 * i, 0, 0));
		_factory.build("go_ahead", tmpM);
	}
	glm::mat4 tmpM(1.0f);

	_factory.build("go_around", glm::translate(tmpM, glm::vec3(10.0, 0, 0)));
	_factory.build("go_around", glm::translate(tmpM, glm::vec3(-1.0, 0, 0)));

	for (int i = 0; i < 10; i++)
	{
		glm::mat4 tmpM(1.0f);
		tmpM = glm::translate(tmpM, glm::vec3(11.0, 0, 1.0));
		tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0));
		tmpM = glm::translate(tmpM, glm::vec3(1.0 * i, 0, 0));
		_factory.build("go_ahead", tmpM);
	}

	tmpM = glm::mat4(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(11.0, 0, 1.0));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0));
	tmpM = glm::translate(tmpM, glm::vec3(10, 0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(0.f), glm::vec3(0.0, 1.0, 0));
	_factory.build("go_around", tmpM);

	auto cam = std::make_unique<Camera>(_factory.getShader("camera"), _factory.getTexture("camera_ico"));
	_camera = cam.get();
	_entities.push_back(std::move(cam));
}

void Maze::processInput()
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera->move(glfwGetTime(), Camera::Direction::Forward);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera->move(glfwGetTime(), Camera::Direction::Back);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera->move(glfwGetTime(), Camera::Direction::Left);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera->move(glfwGetTime(), Camera::Direction::Right);

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);
	
	_camera->rotate({ -(xpos - 1024/2), -(ypos-768/2) });


	glfwSetTime(0); //Wyzeruj licznik czasu
	glfwSetCursorPos(_window, 1024 / 2, 768 / 2);

}

void Maze::renderWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& entity : _entities)
		entity->draw(glm::perspective(50.0f * 3.14f / 180.0f, 1.0f, 0.1f, 50.0f), _camera->getVMatrix(), _camera->getPos());

	glfwSwapBuffers(_window);
}

void Maze::poolEvents()
{
	glfwPollEvents();
}

