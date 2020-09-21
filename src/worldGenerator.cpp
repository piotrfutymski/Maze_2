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
	double x, y, z;
	float angle;
	int param;

	while (file >> type >> x >> y >> z >> angle >> param)
	{
		glm::mat4 PO(1.0f);

		PO = glm::translate(PO, glm::vec3(x, y, z));
		PO = glm::rotate(PO, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));

		if (type == 0)
			this->buildRoofFloor(PO, e, param);
		if (type == 1)
			this->buildWalls(PO, e, param);
		if (type == 2)
			this->buildStairs(PO, e);
	}
	file.close();
}

/*void WorldGenerator::buildBaseMazeElement(const glm::vec3 & p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
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

	tmpM = glm::mat4{ 1.0f };
	tmpM = glm::translate(tmpM, glm::vec3(0.5, 1.4, 0));
	tmpM = glm::scale(tmpM, glm::vec3(0.01, 0.01, 0.01));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(0.0, 0, 1.0));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(0.0, 0, 1.0));
	this->buildSkull(glm::vec3(p.x, p.y, p.z),pos * tmpM, e);
}

void WorldGenerator::buildWallElement(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::mat4 tmpM(1.0f);
	this->buildWall(pos * tmpM, e);
	tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	this->buildWall(pos * tmpM, e);
}*/

void WorldGenerator::buildRoofFloor(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int h)
{
	glm::mat4 tmpM(1.0f);

	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
	this->buildFloorUnit(pos * tmpM, e);

	tmpM = glm::translate( tmpM, glm::vec3(0, 0, -h) );
	this->buildCailUnit(pos * tmpM, e);
}

void WorldGenerator::buildWalls(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int h)
{
	glm::mat4 tmpM(1.0f);
	for (int i = 0; i < h; i++)
	{
		this->buildUnit(pos * tmpM, e);
		tmpM = glm::translate(tmpM, glm::vec3(0, 1.0, 0));
	}
}

void WorldGenerator::buildStairs(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::mat4 tmpM(1.0f);
	tmpM = glm::scale(tmpM, glm::vec3(1, 0.25, 1));
	this->buildUnit(pos * tmpM, e);
	tmpM = glm::mat4(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.25, -0.5));
	tmpM = glm::scale(tmpM, glm::vec3(1, 0.25, 1));
	this->buildUnit(pos * tmpM, e);
	tmpM = glm::mat4(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.25, 0));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
	tmpM = glm::scale(tmpM, glm::vec3(1, 0.5, 1));
	this->buildUnit(pos * tmpM, e);
	tmpM = glm::mat4(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.5, -0.5));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
	tmpM = glm::scale(tmpM, glm::vec3(1, 0.5, 1));
	this->buildUnit(pos * tmpM, e);

}

void WorldGenerator::buildUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::buildFloorUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _models["unit"].get(), _textures["stone"].get(), _textures["stone"].get(), _textures["stone"].get(), pos));
}

void WorldGenerator::buildCailUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _models["unit"].get(), _textures["cail"].get(), _textures["cail"].get(), _textures["cail"].get(), pos));
}

void WorldGenerator::buildSkull(const glm::vec3 & p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Skull>(_shaders["base"].get(), _models["skull"].get(), _textures["skull"].get(), _textures["skull"].get(), _textures["skull"].get(),p, pos));
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
	_textures.emplace("skull", std::make_unique<Texture>("data/textures/skull.png"));
	_textures.emplace("stone", std::make_unique<Texture>("data/textures/stone.png"));
	_textures.emplace("cail", std::make_unique<Texture>("data/textures/stoneCail.png"));
}

void WorldGenerator::loadModels()
{
	_models.emplace("unit", std::make_unique<Model>("data/models/unit.obj"));
	_models.emplace("skull", std::make_unique <Model>("data/models/skull.obj"));
}
