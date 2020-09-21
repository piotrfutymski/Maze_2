#pragma once
#include "object.h"

class Door : public Object
{
public:
	Door(ShaderProgram* p, ShaderProgram* s, Model* m, Texture* td, Texture* th, Texture* tn, int i,  const glm::mat4& M = glm::mat4(1.0f));

	virtual void update(float dt);

private:

	float H = 0;

	float speed = 0.25;

	glm::mat4 baseM;

	int id;
	
};