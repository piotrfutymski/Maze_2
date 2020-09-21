#pragma once
#include "object.h"


class Skull : public Object
{
public:
	Skull(ShaderProgram* p, ShaderProgram* s, Model* m, Texture* td, Texture* th, Texture* tn, const glm::vec3 & pp, const glm::mat4& M = glm::mat4(1.0f));

	virtual void update(float dt);

private:

	int state = 0;

	float angle = 0;

	float speed = 30;

	glm::mat4 baseM;

	glm::vec3 _pos;

};
