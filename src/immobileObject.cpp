#include "immobileObject.h"

void ImmobileObject::draw(const glm::mat4& P, const glm::mat4& V)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _txt.get());

	glUseProgram(_shaderProgram.getID());

	glUniformMatrix4fv(_shaderProgram.u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(_shaderProgram.u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(_shaderProgram.u("M"), 1, false, glm::value_ptr(_M));

	glUniform1i(_shaderProgram.u("tex"), 0);

	glBindVertexArray(_mod.get());

	glDrawArrays(GL_TRIANGLES, 0, _mod.count());
}
