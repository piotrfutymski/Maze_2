#pragma once
#include "object.h"
#include "lightSrc.h"


struct Particle {
    glm::vec3 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle()
        : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class Torch : public Object
{
public:
    Torch(ShaderProgram* p, ShaderProgram* s, ShaderProgram* l, Model* m, Texture* td, Texture* th, Texture* tn, int id, const glm::vec3& pos, const glm::mat4& M = glm::mat4(1.0f));

    virtual void update(float dt);

    virtual void draw();


private:

    glm::vec3 baseLColor = { 0.9, 0.6, 0 };

    int id;

    glm::vec3 _pos;

    std::unique_ptr<Model> _empty;
    std::unique_ptr<LightSrc> _Lsrc;
};