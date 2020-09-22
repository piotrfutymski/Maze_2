#include "troch.h"

bool to_kill(const Particle & p)
{
	return p.Life <= 0;
}


Torch::Torch(ShaderProgram* p, ShaderProgram* s, ShaderProgram* l, Model* m, Texture* td, Texture* th, Texture* tn, int i, const glm::vec3& pos,
	ShaderProgram* pp, Texture* pt, Model* pm, const glm::mat4& M)
	:Object(p,s,m,td,th,tn,M), _particleModel(pm), _particleShader(pp), _particleTxt(pt)
{
	_pos.x = pos.x;
	_pos.y = pos.y + 0.433 * 8.0 /5.0;
	_pos.z = pos.z + 0.4;

	id = i;
	_empty = std::make_unique < Model>();
	_Lsrc = std::make_unique<LightSrc>(l, _empty.get(), M, _pos, baseLColor);
}

void Torch::update(float dt)
{
	_Lsrc->update(dt);

	for (auto& x : _particles)
	{
		x.Life -= dt;
		auto u = x.Life / x.FLife;
		x.Color.a = 1.0 * u;
		x.Color.g = 1.0 * u;

		if (u < 0.3)
		{
			x.Color.a = 2.0 * u;
			x.Color.r = 0.3 * u;
			x.Color.g = 0.0;
		}
		x.Position += x.Velocity * dt;
	}

	_particles.erase(std::remove_if(_particles.begin(), _particles.end(), to_kill), _particles.end());

	if (Environment::objectStates[id] != 3)
		_Lsrc->setStrength(0.0);
	else
	{
		_Lsrc->setStrength(1.0);
		if (_particles.size() < 10000)
		{
			int num = 1000 * dt;
			int i = 0;
			while (_particles.size() < 10000 && i < num)
			{
				this->createParticle();
				++i;
			}
		}

	}

}

void Torch::draw()
{
	this->Object::draw();
	_Lsrc->draw();

	for (auto& x : _particles)
	{
		glUseProgram(_particleShader->get());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _particleTxt->get());
		glUniform1i(_particleShader->u("tex"), 0);

		glm::mat4 M(1.0);
		M = glm::translate(M, x.Position);
		auto u = 10.0 + 10 *  (1 - x.Life / x.FLife);
		M = glm::scale(M, glm::vec3(0.005 * u, 0.005 * u, 0.005 * u));

		glUniformMatrix4fv(_particleShader->u("P"), 1, false, glm::value_ptr(Environment::P));
		glUniformMatrix4fv(_particleShader->u("V"), 1, false, glm::value_ptr(Environment::V));
		glUniformMatrix4fv(_particleShader->u("M"), 1, false, glm::value_ptr(M));

		glUniform4fv (_particleShader->u("color"), 1, glm::value_ptr(x.Color));

		glBindVertexArray(_particleModel->get());
		glDrawArrays(GL_TRIANGLES, 0, _particleModel->count());
	}
}

void Torch::createParticle()
{
	double posX = -0.2;
	double posY = -0.2;
	double posZ = -0.2;
	float angleV = -20;
	float angleA = std::rand()%360;
	double speed = 0;
	double lifetime = 0.5;

	for (int i = 0; i < 10; i++)
	{
		posX += double(std::rand() % 100) / 2500.0;
		posY += double(std::rand() % 100) / 2500.0;
		posZ += double(std::rand() % 100) / 2500.0;
		angleV += (std::rand() % 100) / 25;

		speed += double(std::rand() % 100) / 500;
		lifetime += double(std::rand() % 100) / 2000.0;
	}

	Particle p;
	p.Color = { 1.0, 1.0, 0.0, 1.0 };
	p.FLife = lifetime;
	p.Life = lifetime;
	p.Position = { posX + _pos.x, posY + _pos.y, posZ + _pos.z };

	glm::vec4 v(0.0, 1.0, 0.0, 0.0);
	glm::mat4 tmpM(1.0f);
	tmpM = glm::rotate(tmpM, glm::radians(angleA), glm::vec3(0, 1.0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(angleV), glm::vec3(1.0, 0.0, 0));

	v = tmpM * v;

	p.Velocity = { v.x, v.y, v.z };
	p.Velocity = glm::normalize(p.Velocity) * float(speed);

	_particles.push_back(p);


}
