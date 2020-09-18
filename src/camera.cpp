#include "Camera.h"

Camera::Camera(ShaderProgram& s, Texture& t):Entity(s), _icoTexture(t)
{
	_icoBuffer = {
		-0.02f, 0.02f, 0.0f, 1.0f,
		-0.02f, -0.02f, 0.0f, 0.0f,
		0.02f, -0.02f, 1.0f, 0.0f,
		-0.02f, -0.02f, 0.0f, 0.0f,
		0.02f, -0.02f, 1.0f, 0.0f,
		0.02f, 0.02f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _icoBuffer.size() * sizeof(GLfloat), _icoBuffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

}

void Camera::move(float t, Direction d)
{
	glm::mat4 r(1.0f);

	if (d == Camera::Direction::Left)
		r = glm::rotate(r, glm::radians(90.0f), _head);
	else if (d == Camera::Direction::Back)
		r = glm::rotate(r, glm::radians(180.0f), _head);
	else if (d == Camera::Direction::Right)
		r = glm::rotate(r, glm::radians(270.0f), _head);

	auto dd = r * glm::vec4(_normal.x, _normal.y, _normal.z, 0.0f);

	_pos.x += dd.x * t* _speed;
	_pos.y += dd.y * t * _speed;
	_pos.z += dd.z * t * _speed;
}

void Camera::rotate(const glm::vec2& move)
{
}

glm::mat4 Camera::getVMatrix()
{
	return glm::lookAt(_pos, _pos + _normal, _head);
}

void Camera::draw(const glm::mat4& P, const glm::mat4& V)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _icoTexture.get());

	glUseProgram(_shaderProgram.getID());
	glUniform1i(_shaderProgram.u("tex"), 0);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
