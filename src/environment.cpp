#include "environment.h"

void Environment::init(const std::string& filename)
{
	P = glm::perspective(60.0f * 3.14f / 180.0f, 1.0f, 0.08f, 50.0f);

	leaversStates = false;

	std::fstream file;
	file.open(filename, std::ios::in);

	int s;
	int x, y;
	double h;

	while (file >> s >> x >> y >> h)
	{
		if (s == 0)
			height_map[x + Area::mapSize / 2 + (y + Area::mapSize / 2) * Area::mapSize].h = h;
		else
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					height_map[x * 4 + i + (Area::mapSize / 2)  + (y * 4 + j + (Area::mapSize / 2 ))  * Area::mapSize].h = h;

	}
	file.close();
}


glm::mat4 Environment::P;
glm::mat4 Environment::V;

glm::vec3 Environment::cameraPosition;

Light Environment::lights[256];
GLuint Environment::lightsCount;

bool Environment::leaversStates;

std::map<int, Area> Environment::height_map;

GLFWwindow* Environment::window;