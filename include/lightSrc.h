#pragma once

#include "environment.h"
#include "entity.h"
#include "model.h"

class LightSrc : public Entity
{
public:
	LightSrc(ShaderProgram* p, Model* m, glm::mat4 M, glm::vec3& pos, glm::vec3& color);
	virtual void draw() override;
	virtual void update(float dt) override;

private:
	Model* _mod;
	glm::mat4 _M;
};