#pragma once
#include "entity.h"

class TestEntity :public Entity
{
public:
	TestEntity(ShaderProgram& p, int i) :Entity(p)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		const GLfloat bufferA[] = {
		-0.9f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-0.7f,  1.0f, 0.0f,
		};
		const GLfloat bufferB[] = {
		0.5f, -1.0f, -1.0f,
		0.9f, -1.0f, -1.0f,
		0.7f,  1.0f, -1.0f,
		};
		if(i == 0)
			glBufferData(GL_ARRAY_BUFFER, sizeof(bufferA), bufferA, GL_STATIC_DRAW);
		else
			glBufferData(GL_ARRAY_BUFFER, sizeof(bufferB), bufferB, GL_STATIC_DRAW);
	
	};


	// Odziedziczono za poœrednictwem elementu Entity
	virtual void draw() override
	{
		glUseProgram(_shaderProgram.getID());
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
	}

private:

	GLuint VAO;
	GLuint VBO;
	
};