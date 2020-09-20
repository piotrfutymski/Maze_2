#include "worldGenerator.h"

void WorldGenerator::init()
{
	this->loadModels();
	this->loadShaders();
	this->loadTextures();
}

void WorldGenerator::load(const std::string& filename, std::vector<std::unique_ptr<Entity>>& e)
{

	e.emplace_back(std::make_unique<Camera>(_shaders["camera"].get(), _textures["camera_ico"].get()));

	std::fstream file;
	file.open(filename, std::ios::in);

	int type;
	int x, z;
	float angle;

	while (file >> type >> x >> z >> angle)
	{
		glm::mat4 PO(1.0f);

		PO = glm::translate(PO, glm::vec3(x, 0, z));
		PO = glm::rotate(PO, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));

		if (type == 0)
			this->buildSimplifiedMazeElement(PO, e);
		else if (type == 1)
			this->buildBaseMazeElement(PO, e);

	}
	file.close();
}

void WorldGenerator::buildBaseMazeElement(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::mat4 tmpM(1.0f);
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.0, 1.0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	this->buildWall(pos * tmpM, e);
}

void WorldGenerator::buildSimplifiedMazeElement(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::mat4 tmpM(1.0f);
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	this->buildWall(pos * tmpM, e);
	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	this->buildWall(pos * tmpM, e);
}

void WorldGenerator::buildWall(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::loadShaders()
{
	_shaders.emplace("base", std::make_unique<ShaderProgram>("data/shaders/v_base_shader.glsl", "data/shaders/f_base_shader.glsl"));
	_shaders.emplace("camera", std::make_unique<ShaderProgram>("data/shaders/v_camera_shader.glsl", "data/shaders/f_camera_shader.glsl"));
}

void WorldGenerator::loadTextures()
{
	_textures.emplace("wall", std::make_unique<Texture>("data/textures/wall.png"));
	_textures.emplace("wall_h", std::make_unique<Texture>("data/textures/wall_height.png"));
	_textures.emplace("wall_n", std::make_unique<Texture>("data/textures/wall_norm.png"));
	_textures.emplace("camera_ico", std::make_unique<Texture>("data/textures/c_ico.png"));
}

void WorldGenerator::loadModels()
{
	_models.emplace("unit", std::make_unique<Model>("data/models/unit.obj"));
}
