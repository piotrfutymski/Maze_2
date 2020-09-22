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
	if (glm::distance(_pos, Environment::cameraPosition) > 7)
		return;

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
	if (_particles.size() > 6400)
		_Lsrc->setStrength(4.0);
	else if (_particles.size() > 5200)
		_Lsrc->setStrength(4.0f - 4.0 *float(6400 - _particles.size()) / 2400.0f);
	else
		_Lsrc->setStrength(2.0 * _particles.size() / 5200);

	if (Environment::objectStates[id] != 3)
		_Lsrc->setStrength(0.0);
	else
	{

		int r = std::rand()%400;

		if (_particles.size() < 6000)
		{	
			int i = 0;
			while (i < r + 10)
			{
				this->createParticle();
				++i;
			}
		}
		for (int i = 0; i < 10; i++)
			this->createParticle();

	}

}

void Torch::shadow(glm::mat4& lightSpaceMatrix)
{
}

void Torch::draw()
{
	if (glm::distance(_pos, Environment::cameraPosition) > 7)
		return;

	this->Object::draw();
	_Lsrc->draw();

	glUseProgram(_particleShader->get());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _particleTxt->get());
	glUniform1i(_particleShader->u("tex"), 0);
	glUniformMatrix4fv(_particleShader->u("P"), 1, false, glm::value_ptr(Environment::P));
	glUniformMatrix4fv(_particleShader->u("V"), 1, false, glm::value_ptr(Environment::V));

	glBindVertexArray(_particleModel->get());

	for (auto& x : _particles)
	{
	
		glm::mat4 M(1.0);
		M = glm::translate(M, x.Position);
		auto u = 8.0 + 10 *  (1 - x.Life / x.FLife);
		M = glm::scale(M, glm::vec3(0.005 * u, 0.005 * u, 0.005 * u));

		glUniformMatrix4fv(_particleShader->u("M"), 1, false, glm::value_ptr(M));
		glUniform4fv (_particleShader->u("color"), 1, glm::value_ptr(x.Color));


		glDrawArrays(GL_TRIANGLES, 0, _particleModel->count());
	}
}

void Torch::createParticle()
{
	double posX = -0.1;
	double posY = -0.1;
	double posZ = -0.1;
	float angleV = -20;
	float angleA = std::rand()%360;
	double speed = 0;
	double lifetime = 0.5;

	for (int i = 0; i < 10; i++)
	{
		posX += double(std::rand() % 100) / 5000.0;
		posY += double(std::rand() % 100) / 5000.0;
		posZ += double(std::rand() % 100) / 5000.0;
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
