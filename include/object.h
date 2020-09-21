#pragma once
#include "entity.h"
#include "model.h"
#include "texture.h"
class Object : public Entity
{
public:
	Object(ShaderProgram* p, ShaderProgram* s, Model* m, Texture* td, Texture * th, Texture * tn, const glm::mat4& M = glm::mat4(1.0f));

	virtual void draw();
	virtual void shadow(glm::mat4& lightSpaceMatrix);
	virtual void update(float dt);


protected:
	glm::mat4 _M;
	Model * _mod;
	Texture * _diffMap;
	Texture * _heightMap;
	Texture * _normMap;

};