#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "entity.h"
#include "texture.h"

class Camera : public Entity
{
public:

	enum class Direction{
	Forward, Back, Left, Right};

	Camera(ShaderProgram& s, Texture& t);

	void move(float t, Direction d);

	void rotate(const glm::vec2& move);

	glm::mat4 getVMatrix();

private:

	glm::vec3 _pos = { 10.0f, 0.0f, 4.0f};
	glm::vec3 _normal = {-1.0f, 0.0f, 0.0f};
	glm::vec3 _head = { 0.0f, 1.0f, 0.0f};
	glm::vec3 _up = { 0.0f, 1.0f, 0.0f };
	float yaw = 0.0f;
	float pitch = 0.0f;

	float _speed = 2.0;
	float _sensivity = 0.1;

	Texture& _icoTexture;
	std::vector<float> _icoBuffer;

	GLuint VBO, VAO;

public:
		// Odziedziczono za poœrednictwem elementu Entity
	virtual void draw(const glm::mat4& P, const glm::mat4& V) override;

};