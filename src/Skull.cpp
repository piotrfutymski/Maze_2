#include "..\include\Skull.h"

Skull::Skull(ShaderProgram* p, Model* m, Texture* td, Texture* th, Texture* tn, const glm::vec3& pp, int i, const glm::mat4& M)
	:Object(p, s, m, td, th, tn, M), _pos(pp), baseM(M), id(i)
{
}

void Skull::update(float dt)
{
	auto f = glm::normalize(_pos - Environment::cameraPosition);

	if (Environment::F_Pressed && glm::distance(_pos, Environment::cameraPosition) < 2.5 && glm::dot(f, Environment::cameraNormal) > 0.98)
	{
		if (Environment::objectStates[id] == 0)
			Environment::objectStates[id] = 1;
		else if (Environment::objectStates[id] == 1)
			Environment::objectStates[id] = 2;
		else if (Environment::objectStates[id] == 2)
			Environment::objectStates[id] = 1;
		else if (Environment::objectStates[id] == 3)
			Environment::objectStates[id] = 2;
	}

	if (angle > 90)
	{
		angle = 90;
		Environment::objectStates[id] = 3;
	}
	if (angle < 0)
	{
		angle = 0;
		Environment::objectStates[id] = 0;
	}

	if (Environment::objectStates[id] == 1 && angle < 90)
		angle += dt * speed;
	if (Environment::objectStates[id] == 2 && angle > 0)
		angle -= dt * speed;

	_M = glm::rotate(baseM, glm::radians(angle), glm::vec3(0, 0, 1));

}
