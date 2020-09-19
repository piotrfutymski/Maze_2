#include "Camera.h"

Camera::Camera(ShaderProgram& s, Texture& t):Entity(s), _icoTexture(t)
{
	_icoBuffer = {
		-0.02f, -0.02f, 0.0f, 0.0f,
		-0.02f, 0.02f, 0.0f, 1.0f,
		0.02f, -0.02f, 1.0f, 0.0f,
		-0.02f, 0.02f, 0.0f, 1.0f,
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
	yaw -= move.x * _sensivity;
	pitch -=move.y * _sensivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(-pitch));
	direction.y = sin(glm::radians(-pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(-pitch));

	_normal = glm::normalize(direction);
	auto cameraRightCoords = glm::normalize(glm::cross(_normal, _up));  
	_head = glm::normalize(glm::cross(cameraRightCoords, _normal));

	/*auto I_ = glm::normalize(glm::cross(_normal, _head));
	glm::mat4 r(1.0f);
	r = glm::rotate(r, glm::radians(90.0f) * _sensivity * move.x, _head);
	r = glm::rotate(r, glm::radians(90.0f) * _sensivity * move.y, I_);

	auto nhead = r * glm::vec4(_head.x, _head.y, _head.z, 0.0f);
	auto nNormal = r * glm::vec4(_normal.x, _normal.y, _normal.z, 0.0f);

	auto J_ = _head;
	auto K_ = -_normal;
	_normal = glm::vec3(nNormal.x, nNormal.y, nNormal.z);
	_head = glm::vec3(nhead.x, nhead.y, nhead.z);*/

}

glm::mat4 Camera::getVMatrix()
{
	return glm::lookAt(_pos, _pos + _normal*100.0f, _head);
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
