#include "LightSrc.h"

LightSrc::LightSrc(ShaderProgram* p, Model* m, glm::mat4 M, const glm::vec3& pos,const glm::vec3& color)
	: Entity(p), _mod(m), _M(M), envID(Environment::lightsCount++)

{
	Environment::lights[envID].color = color;
    Environment::lights[envID].strength = 1.f;
    this->changePos(pos);

    // Creating Depth Textures
    for (int i = 0; i < 6; i++)
    {
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

        Environment::lights[envID].depthMap[i] = depthMap;
    }
}

void LightSrc::changePos(const glm::vec3& pos)
{
    static glm::mat4 lightProjection, lightView;
    static float near_plane = .1f, far_plane = 50.f;

    static glm::vec3 directions[] =
    {
        glm::vec3(1.f,0.f,0.f),  glm::vec3(0.f, 1.f, 0.f),  glm::vec3(0.f,0.f,1.f),   // x, y, z
        glm::vec3(-1.f,0.f,0.f),  glm::vec3(0.f, -1.f, 0.f),  glm::vec3(0.f,0.f,-1.f)   // -x, -y, -z
    };

    lightProjection = glm::perspective(glm::radians(90.f), (GLfloat)Environment::smapWidth / (GLfloat)Environment::smapHeight, near_plane, far_plane);
    for (int i = 0; i < 6; i++)
    {
        lightView = glm::lookAt(pos, pos + directions[i], directions[(i + 1) % 6]);
        Environment::lights[envID].lightSpaceMatrix[i] = lightProjection * lightView;
    }
    Environment::lights[envID].position = pos;
}

void LightSrc::changeColor(const glm::vec3& color)
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