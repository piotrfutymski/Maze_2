#include "LightSrc.h"

LightSrc::LightSrc(ShaderProgram* p, Model* m, glm::mat4 M, glm::vec3& pos, glm::vec3& color)
	: Entity(p), _mod(m), _M(M) 
{
	Environment::lights[Environment::lightsCount].position = pos;
	Environment::lights[Environment::lightsCount++].color = color;
}

void LightSrc::draw()
{
	glUseProgram(_shaderProgram->get());

	glUniformMatrix4fv(_shaderProgram->u("P"), 1, false, glm::value_ptr(Environment::P));
	glUniformMatrix4fv(_shaderProgram->u("V"), 1, false, glm::value_ptr(Environment::V));
	glUniformMatrix4fv(_shaderProgram->u("M"), 1, false, glm::value_ptr(_M));

	glBindVertexArray(_mod->get());

	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
}

void LightSrc::update(float dt)
{

}
