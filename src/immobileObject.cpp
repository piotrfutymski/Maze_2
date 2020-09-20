#include "immobileObject.h"

void ImmobileObject::draw(const glm::mat4& P, const glm::mat4& V, const glm::vec3& cameraPos)
{

	glUseProgram(_shaderProgram->getID());

	glActiveTexture(GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE_2D, _txts[0].get());
	glUniform1i(_shaderProgram->u("diffuseMap"), 0);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, _txts[1].get());
	glUniform1i(_shaderProgram->u("depthMap"), 1);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, _txts[2].get());
	glUniform1i(_shaderProgram->u("normalMap"), 2);

	glUniform3fv(_shaderProgram->u("viewPos"), 1, glm::value_ptr(cameraPos));

	glUniformMatrix4fv(_shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(_shaderProgram->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(_shaderProgram->u("M"), 1, false, glm::value_ptr(_M));

	glBindVertexArray(_mod->get());

	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
}
