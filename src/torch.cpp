#include "troch.h"

Torch::Torch(ShaderProgram* p, ShaderProgram* s, ShaderProgram* l, Model* m, Texture* td, Texture* th, Texture* tn, int i, const glm::vec3& pos, const glm::mat4& M)
	:Object(p,s,m,td,th,tn,M)
{
	_pos.x = pos.x;
	_pos.y = pos.y + 0.866;
	_pos.z = pos.z + 0.5;

	id = i;
	_empty = std::make_unique < Model>();
	_Lsrc = std::make_unique<LightSrc>(l, _empty.get(), M, _pos, baseLColor);
}

void Torch::update(float dt)
{
	_Lsrc->update(dt);
	auto f = glm::normalize(_pos - Environment::cameraPosition);
	if (Environment::F_Pressed && glm::distance(_pos, Environment::cameraPosition) < 3.0 && glm::dot(f, Environment::cameraNormal) > 0.98)
	{
		if (Environment::objectStates[id] == 0)
			Environment::objectStates[id] = 1;
		else 
			Environment::objectStates[id] = 0;
	}
}

void Torch::draw()
{
	this->Object::draw();
	_Lsrc->draw();
}
