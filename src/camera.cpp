#include "Camera.h"

Camera::Camera(ShaderProgram* s, Texture* t):Entity(s), _icoTexture(t)
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

	auto nposX = _pos.x + dd.x * t * _speed;
	auto nposY = _pos.y + dd.y * t * _speed;
	auto nposZ = _pos.z + dd.z * t * _speed;

	int oldArea = (floor(Area::edge *_pos.x) + Area::mapSize / 2) +
		(floor(Area::edge * _pos.z) + Area::mapSize / 2) * Area::mapSize;

	int area = (floor(Area::edge * nposX) + Area::mapSize / 2) +
		(floor(Area::edge * nposZ) + Area::mapSize / 2) * Area::mapSize;

	if (Environment::height_map.find(area) == Environment::height_map.end())
	{
		return;
	}

	bool P1 = false, P2 = false, P3 = false, P4 = false;

	if (Environment::height_map.find(area + 1) == Environment::height_map.end())
		P1 = true;
	if (Environment::height_map.find(area - 1) == Environment::height_map.end())
		P2 = true;
	if (Environment::height_map.find(area + Area::mapSize) == Environment::height_map.end())
		P3 = true;
	if (Environment::height_map.find(area - Area::mapSize) == Environment::height_map.end())
		P4 = true;


	if (nposX - float(floor(nposX)) > 0.90f && P1)
		return;
	if (nposX - float(floor(nposX)) < 0.1f && P2)
		return;
	if (nposZ - float(floor(nposZ)) > 0.90f && P3)
		return;
	if (nposZ - float(floor(nposZ)) < 0.1f && P4)
		return;

	if (Environment::height_map[area].h > 0.9 + Environment::height_map[oldArea].h)
		return;

	_pos.y = Environment::height_map[area].h;
	_pos.x = nposX;
	_pos.z = nposZ;
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


}


void Camera::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _icoTexture->get());

	glUseProgram(_shaderProgram->get());
	glUniform1i(_shaderProgram->u("tex"), 0);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Camera::update(float dt)
{
	if (glfwGetKey(Environment::window, GLFW_KEY_W) == GLFW_PRESS)
		this->move(dt, Camera::Direction::Forward);
	if (glfwGetKey(Environment::window, GLFW_KEY_S) == GLFW_PRESS)
		this->move(dt, Camera::Direction::Back);
	if (glfwGetKey(Environment::window, GLFW_KEY_A) == GLFW_PRESS)
		this->move(dt, Camera::Direction::Left);
	if (glfwGetKey(Environment::window, GLFW_KEY_D) == GLFW_PRESS)
		this->move(dt, Camera::Direction::Right);

	double xpos, ypos;
	glfwGetCursorPos(Environment::window, &xpos, &ypos);

	this->rotate({ -(xpos - 1024 / 2), -(ypos - 768 / 2) });

	Environment::V = glm::lookAt(_pos, _pos + _normal * 100.0f, _head);
	Environment::cameraPosition = _pos;
	Environment::cameraNormal = _normal;
	glfwSetCursorPos(Environment::window, 1024 / 2, 768 / 2);
}


