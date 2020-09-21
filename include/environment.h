#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <fstream>

struct Light
{
	glm::vec3 position;
	glm::vec3 color;
};

struct Area
{
	double h;
	constexpr static double edge = 4;
	constexpr static int mapSize = 1024;
};

class Environment
{
public:

	static void init(const std::string & filename);

	static glm::mat4 P;
	static glm::mat4 V;

	static glm::vec3 cameraPosition;

	static Light lights[256];
	static GLuint lightsCount;

	static bool leaversStates;

	static std::map<int, Area> height_map;

	static GLFWwindow* window;

	static bool F_Pressed;



};
