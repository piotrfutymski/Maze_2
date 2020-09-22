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
	glm::mat4 lightSpaceMatrix;
	unsigned int depthMap;
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

	static void loadHeights(const std::string& filename);
	static void unloadHeights(const std::string& filename);

	static glm::mat4 P;
	static glm::mat4 V;

	static glm::vec3 cameraPosition;
	static glm::vec3 cameraNormal;

	static int objectStates[15];

	static Light lights[8];
	static GLuint lightsCount;

	static std::map<int, Area> height_map;

	static GLFWwindow* window;
	static unsigned int windowWidth, windowHeight;

	static bool F_Pressed;
	static bool E_Pressed;

	static unsigned int depthMapFBO;
	static const unsigned int smapWidth = 2048, smapHeight = 2048;
};
