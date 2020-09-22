#include "LightSrc.h"

LightSrc::LightSrc(ShaderProgram* p, Model* m, glm::mat4 M, const glm::vec3& pos,const glm::vec3& color)
	: Entity(p), _mod(m), _M(M), envID(Environment::lightsCount++)

{
	Environment::lights[envID].position = pos;
	Environment::lights[envID].color = color;
    Environment::lights[envID].strength = 1.f;

    glm::mat4 lightProjection, lightView;
    float near_plane = 0.1f, far_plane = 80.f;

    lightView = glm::lookAt(pos, glm::vec3(2.5f, 1.5f, 0.f), glm::vec3(0.0, 1.0, 0.0));
    lightProjection = glm::perspective(glm::radians(90.f), (GLfloat)Environment::smapWidth / (GLfloat)Environment::smapHeight, near_plane, far_plane);
    Environment::lights[envID].lightSpaceMatrix = lightProjection * lightView;

    // Creating Depth Texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Environment::smapWidth, Environment::smapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    Environment::lights[envID].depthMap = depthMap;
}

void LightSrc::changePos(glm::vec3& pos)
{
    Environment::lights[envID].position = pos;
}

void LightSrc::changeColor(glm::vec3& color)
{
    Environment::lights[envID].color = color;
}

void LightSrc::setStrength(float scale)
{
    Environment::lights[envID].strength = scale;
}


void LightSrc::draw()
{
	glUseProgram(_shaderProgram->get());
  
	glUniformMatrix4fv(_shaderProgram->u("P"), 1, false, glm::value_ptr(Environment::P));
	glUniformMatrix4fv(_shaderProgram->u("V"), 1, false, glm::value_ptr(Environment::V));
	glUniformMatrix4fv(_shaderProgram->u("M"), 1, false, glm::value_ptr(_M));

	glBindVertexArray(_mod->get());

	glDrawArrays(GL_TRIANGLES, 0, _mod->count());
}

void LightSrc::update(float dt)
{

}
