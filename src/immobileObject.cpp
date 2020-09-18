#include "immobileObject.h"

void ImmobileObject::draw()
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(10.0f, 0.0f, 4.0f),
		glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 P = glm::perspective(50.0f * 3.14f / 180.0f, 1.0f, 0.2f, 50.0f);


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
