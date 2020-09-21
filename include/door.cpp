#include "door.h"

Door::Door(ShaderProgram* p, Model* m, Texture* td, Texture* th, Texture* tn, int i, const glm::mat4& M)
	:Object(p, m, td, th, tn, M), baseM(M), id(i)
{
}

void Door::update(float dt)
{
	if (H > 1)
	{
		H = 1;
		std::string fname = "data/height_map" + std::to_string(id) + ".txt";
		Environment::loadHeights(fname);
	}
	if (H < 0)
	{
		H = 0;
		std::string fname = "data/height_map" + std::to_string(id) + ".txt";
		Environment::unloadHeights(fname);
	}

	if (Environment::objectStates[id] == 1 && H < 1)
		H += dt * speed;
	if (Environment::objectStates[id] == 2 && H > 0)
		H -= dt * speed;

	_M = glm::translate(baseM, glm::vec3(0, H, 0));
}
