#include "modelFactory.h"

ModelFactory::ModelFactory(std::vector<std::unique_ptr<Entity>>& e): _entities(e)
{

}

void ModelFactory::init()
{
	this->loadModels();
	this->loadShaders();
	this->loadTextures();
	this->createGoAhead();
	this->createGoAround();
}



void ModelFactory::build(const std::string& name, const glm::mat4& pos)
{
	for (auto& x : _elements[name])
	{
		auto mod = std::make_unique<ImmobileObject>(_shaders["base"].get(), x.m, std::vector<Texture>({ *_textures["wall"].get(), *_textures["wall_h"].get(), *_textures["wall_n"].get() }), pos * x.mat);
		_entities.push_back(std::move(mod));
	}

}

Model* ModelFactory::getModel(const std::string& name)
{
	return _models[name].get();
}

Texture* ModelFactory::getTexture(const std::string& name)
{
	return _textures[name].get();
}

ShaderProgram* ModelFactory::getShader(const std::string& name)
{
	return _shaders[name].get();
}

void ModelFactory::createGoAhead()
{
	std::vector<FactoryElement> el;
	glm::mat4 tmpM(1.0f);
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	el.emplace_back( _textures["wall"].get(), _models["unit"].get(), tmpM );
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	el.emplace_back( _textures["wall"].get(), _models["unit"].get(), tmpM );
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	el.emplace_back( _textures["wall"].get(), _models["unit"].get(), tmpM );
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.0, 1.0));
	el.emplace_back( _textures["wall"].get(), _models["unit"].get(), tmpM );
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	el.emplace_back( _textures["wall"].get(), _models["unit"].get(), tmpM );

	_elements["go_ahead"] = el;

}

void ModelFactory::createGoAround()
{
	std::vector<FactoryElement> el;
	glm::mat4 tmpM(1.0f);
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::translate(tmpM, glm::vec3(1.0, 0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0));
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	el.emplace_back(_textures["wall"].get(), _models["unit"].get(), tmpM);

	_elements["go_around"] = el;
}

void ModelFactory::loadShaders()
{
	_shaders.emplace("base", std::make_unique<ShaderProgram>("data/shaders/v_base_shader.glsl", "data/shaders/f_base_shader.glsl"));
	_shaders.emplace("camera", std::make_unique<ShaderProgram>("data/shaders/v_camera_shader.glsl", "data/shaders/f_camera_shader.glsl"));
}

void ModelFactory::loadTextures()
{
	_textures.emplace("wall", std::make_unique<Texture>("data/textures/wall.png"));
	_textures.emplace("wall_h", std::make_unique<Texture>("data/textures/wall_height.png"));
	_textures.emplace("wall_n", std::make_unique<Texture>("data/textures/wall_norm.png"));
	_textures.emplace("camera_ico", std::make_unique<Texture>("data/textures/c_ico.png"));
}

void ModelFactory::loadModels()
{
	auto tmp = std::make_unique<Model>();
	tmp->loadMesh("data/models/wall.obj");
	_models.emplace("unit", std::move(tmp));
}

