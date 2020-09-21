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

		glm::vec3 pos(x, y, z);

		PO = glm::translate(PO, pos);
		PO = glm::rotate(PO, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));

		if (type == 0)
			this->buildRoofFloor(PO, e, param);
		if (type == 1)
			this->buildWalls(PO, e, param);
		if (type == 2)
			this->buildStairs(PO, e);
		if (type == 3)
			this->buildLightSource(PO, pos, param, e);
		if (type == 4)
			this->buildSkull(pos, PO, e, param);
		if (type == 5)
			this->buildDoor(PO, e, param);
	}
	file.close();
}

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

void WorldGenerator::buildLightSource(const glm::mat4& M, glm::vec3& pos, int c, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::vec3 color;
	if (c == 0)
		color = glm::vec3(0.5, 0.5, 1.0);

	glm::mat4 tmpM(1.0f);
	tmpM = glm::scale(tmpM, glm::vec3(0.01, 0.01, 0.01));

	e.emplace_back(std::make_unique<LightSrc>(_shaders["light_src"].get(), _models["skull"].get(), M * tmpM, pos, color));
}

void WorldGenerator::buildSkull(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int pa)
{
	glm::mat4 tmpM(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(0, 0.1, 0));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
	tmpM = glm::scale(tmpM, glm::vec3(0.01, 0.01, 0.01));
	e.emplace_back(std::make_unique<Skull>(_shaders["base"].get(), _shaders["shadow"].get(), _models["skull"].get(), _textures["skull"].get(), _textures["skull"].get(), _textures["skull"].get(), p, pa, pos * tmpM));
}

void WorldGenerator::buildDoor(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int param)
{
	e.emplace_back(std::make_unique<Door>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), param, pos));
}

void WorldGenerator::buildUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::buildFloorUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["stone"].get(), _textures["stone_h"].get(), _textures["stone_n"].get(), pos));
}

void WorldGenerator::buildCailUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["cail"].get(), _textures["cail"].get(), _textures["cail"].get(), pos));
}

void WorldGenerator::loadShaders()
{
	_shaders.emplace("base", std::make_unique<ShaderProgram>("data/shaders/v_base_shader.glsl", "data/shaders/f_base_shader.glsl"));
	_shaders.emplace("camera", std::make_unique<ShaderProgram>("data/shaders/v_camera_shader.glsl", "data/shaders/f_camera_shader.glsl"));
	_shaders.emplace("light_src", std::make_unique<ShaderProgram>("data/shaders/v_light_src_shader.glsl", "data/shaders/f_light_src_shader.glsl"));
	_shaders.emplace("shadow", std::make_unique<ShaderProgram>("data/shaders/v_shadow_shader.glsl", "data/shaders/f_shadow_shader.glsl"));
}

void WorldGenerator::loadTextures()
{
	_textures.emplace("camera_ico", std::make_unique<Texture>("data/textures/c_ico.png"));
	_textures.emplace("skull", std::make_unique<Texture>("data/textures/skull.png"));
	_textures.emplace("stone", std::make_unique<Texture>("data/textures/stone.png"));
	_textures.emplace("stone_h", std::make_unique<Texture>("data/textures/stone_h.png"));
	_textures.emplace("stone_n", std::make_unique<Texture>("data/textures/stone_n.png"));
	_textures.emplace("wall", std::make_unique<Texture>("data/textures/wall.png"));
	_textures.emplace("wall_h", std::make_unique<Texture>("data/textures/wall_h.png"));
	_textures.emplace("wall_n", std::make_unique<Texture>("data/textures/wall_n.png"));
	_textures.emplace("cail", std::make_unique<Texture>("data/textures/stoneCail.png"));
}

void WorldGenerator::loadModels()
{
	_models.emplace("unit", std::make_unique<Model>("data/models/unit.obj"));
	_models.emplace("skull", std::make_unique <Model>("data/models/skull.obj"));
}
