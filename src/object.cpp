#include "object.h"


Object::Object(ShaderProgram* p, Model* m, Texture* td, Texture* th, Texture* tn, const glm::mat4& M)
	:Entity(p), _mod(m), _diffMap(td), _heightMap(th), _normMap(tn), _M(M)
{
}

void Object::draw()
{
	glUseProgram(_shaderProgram->get());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _diffMap->get());
	glUniform1i(_shaderProgram->u("diffuseMap"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _heightMap->get());
	glUniform1i(_shaderProgram->u("heightMap"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _normMap->get());
	glUniform1i(_shaderProgram->u("normalMap"), 2);

	glUniform3fv(_shaderProgram->u("viewPos"), 1, glm::value_ptr(Environment::cameraPosition));

	glUniformMatrix4fv(_shaderProgram->u("P"), 1, false, glm::value_ptr(Environment::P));
	glUniformMatrix4fv(_shaderProgram->u("V"), 1, false, glm::value_ptr(Environment::V));
	glUniformMatrix4fv(_shaderProgram->u("M"), 1, false, glm::value_ptr(_M));

	glBindVertexArray(_mod->get());
	
	//TO DO - lights to shader!

	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
}

void Object::update(float dt)
{
	// nothing happens
}


