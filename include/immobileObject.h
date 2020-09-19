#pragma once
#include "entity.h"
#include "model.h"
#include "texture.h"
class ImmobileObject : public Entity
{
public:
	ImmobileObject(ShaderProgram * p, Model * m, Texture * t, const glm::mat4 & M = glm::mat4(1.0f)) : Entity(p), _mod(m), _txt(t), _M(M) {}

	virtual void draw(const glm::mat4& P, const glm::mat4& V) override;

private:
	glm::mat4 _M;
	Model * _mod;
	Texture * _txt;
};