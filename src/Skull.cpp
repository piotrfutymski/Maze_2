#include "..\include\Skull.h"

Skull::Skull(ShaderProgram* p, Model* m, Texture* td, Texture* th, Texture* tn, const glm::vec3& pp, const glm::mat4& M)
	:Object(p, m, td, th, tn, M), _pos(pp)
{
	baseM = M;
}

void Skull::update(float dt)
{

	if (Environment::F_Pressed && glm::distance(_pos, Environment::cameraPosition) < 1.0)
	{
		if (state == 0)
			state = 1;
		else if (state == 1)
			state = 2;
		else if (state == 2)
			state = 1;
		else if (state == 3)
			state = 2;
	}

	if (angle > 90)
	{
		angle = 90;
		state = 3;
	}
	if (angle < 0)
	{
		angle = 0;
		state = 0;
	}

	if (state == 1 && angle < 90)
		angle += dt * speed;
	if (state == 2 && angle > 0)
		angle -= dt * speed;

	_M = glm::rotate(baseM, glm::radians(angle), glm::vec3(0, 0, 1));

}
