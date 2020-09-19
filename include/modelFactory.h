#pragma once

#include "entity.h"
#include "immobileObject.h"
#include "map"

struct FactoryElement
{
	FactoryElement(Texture* tt, Model* mm, const glm::mat4& mma) : t{ tt }, m{ mm }, mat{ mma }{};

	Texture * t;
	Model* m;
	glm::mat4 mat;
};


class ModelFactory
{
public:

	ModelFactory(std::vector<std::unique_ptr<Entity>>& e);

	void init();

	void build(const std::string & name, const glm::mat4& pos);

	Model* getModel(const std::string& name);
	Texture* getTexture(const std::string& name);
	ShaderProgram* getShader(const std::string& name);

private:

	std::map<std::string, std::unique_ptr<Model>> _models;
	std::map<std::string, std::unique_ptr<Texture>> _textures;
	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaders;

	std::vector<std::unique_ptr<Entity>>& _entities;

	std::map<std::string, std::vector<FactoryElement>> _elements;

private:

	void loadShaders();
	void loadTextures();
	void loadModels();

	void createGoAhead();
	void createGoAround();

};