#include "object.h"

Object::Object(ShaderProgram* p, ShaderProgram* s, Model* m, Texture* td, Texture* th, Texture* tn, const glm::mat4& M)
	:Entity(p,s), _mod(m), _diffMap(td), _heightMap(th), _normMap(tn), _M(M)
{
}

void Object::shadow(glm::mat4& lightSpaceMatrix)
{
	glUseProgram(_shadowShader->get());

	glUniformMatrix4fv(_shadowShader->u("lightSpaceMatrix"), 1, false, glm::value_ptr(lightSpaceMatrix));
	glUniformMatrix4fv(_shadowShader->u("M"), 1, false, glm::value_ptr(_M));

	glBindVertexArray(_mod->get());
	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
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
	
	glUniform1i(_shaderProgram->u("lightCount"), Environment::lightsCount);

	std::string s = "lightPos[";
	for (int i = 0; i < Environment::lightsCount; i++)
		glUniform3fv(_shaderProgram->u(((s + (char)('0'+i))+']').c_str()), 1, glm::value_ptr(Environment::lights[i].position));

	s = "lightColors[";
	for (int i = 0; i < Environment::lightsCount; i++)
		glUniform3fv(_shaderProgram->u(((s + (char)('0' + i)) + ']').c_str()), 1, glm::value_ptr(Environment::lights[i].color * Environment::lights[i].strength));

	s = "lightSpaceMatrix[";
	for (int i = 0; i < Environment::lightsCount; i++)
		glUniformMatrix4fv(_shaderProgram->u(((s + (char)('0' + i)) + ']').c_str()), 1, false, glm::value_ptr(Environment::lights[i].lightSpaceMatrix));

	s = "sMap[";
	for (int i = 0; i < Environment::lightsCount; i++)
	{
		glActiveTexture(GL_TEXTURE3 + i);
		glBindTexture(GL_TEXTURE_2D, Environment::lights[i].depthMap);
		glUniform1i(_shaderProgram->u(((s + (char)('0' + i)) + ']').c_str()), 3+i);
	}

	glUniform1i(_shaderProgram->u("lightCount"), Environment::lightsCount);

	glBindVertexArray(_mod->get());
	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
}

void Object::update(float dt)
{
	// nothing happens
}


