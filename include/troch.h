#pragma once
#include "object.h"
#include "lightSrc.h"
#include "ctime";


struct Particle {
    glm::vec3 Position, Velocity;
    glm::vec4 Color;
    float     Life;
    float     FLife;

};

class Torch : public Object
{
public:
    Torch(ShaderProgram* p, ShaderProgram* s, ShaderProgram* l, Model* m, Texture* td, Texture* th, Texture* tn, int id, const glm::vec3& pos,
        ShaderProgram *pp, Texture * pt, Model *pm, const glm::mat4& M = glm::mat4(1.0f));

    virtual void update(float dt);

    virtual void draw();


private:

    void createParticle();

    std::vector<Particle> _particles;

    glm::vec3 baseLColor = { 0.9, 0.6, 0 };

    int id;

    glm::vec3 _pos;

    Texture* _particleTxt;
    ShaderProgram * _particleShader;
    Model * _particleModel;
    std::unique_ptr<Model> _empty;
    std::unique_ptr<LightSrc> _Lsrc;
};