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
		if (type == 6)
			this->buildTorch(pos, PO, e, param);
		if (type == 7)
			this->buildDesc(PO, e);
		if (type == 8)
			this->buildrock(PO, e);
	}
	file.close();
}

void WorldGenerator::buildRoofFloor(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int h)
{
	glm::mat4 tmpM(1.0f);

	tmpM = glm::translate(tmpM, glm::vec3(0.f, 0.f, 1.f));

	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
	this->buildFloorUnit(pos * tmpM, e);

	tmpM=glm::mat4(1.0f);
	tmpM = glm::rotate(tmpM, glm::radians(90.0f), glm::vec3(1.0, 0, 0));

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
		color = glm::vec3(0., 0., 1.0);

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

void WorldGenerator::buildTorch(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int param)
{
	glm::mat4 tmpM(1.0f);
	tmpM = glm::rotate(tmpM, glm::radians(120.0f), glm::vec3(1.0, 0, 0));
	tmpM = glm::scale(tmpM, glm::vec3(0.5, 0.5, 0.5));
	e.emplace_back(std::make_unique<Torch>(_shaders["base"].get(), _shaders["shadow"].get(), _shaders["light_src"].get(), _models["torch"].get(), _textures["t"].get(), _textures["t_h"].get(), _textures["t_n"].get(), param, p, 
		_shaders["particle"].get(), _textures["particle"].get(), _models["particle"].get() ,pos * tmpM));
}

void WorldGenerator::buildDesc(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	glm::mat4 tmpM(1.0f);
	tmpM = glm::translate(tmpM, glm::vec3(1.15, 0, 0.75));
	tmpM = glm::scale(tmpM, glm::vec3(0.01, 0.01, 0.01));
	tmpM = glm::rotate(tmpM, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["desk"].get(), _textures["desk"].get(), _textures["desk_h"].get(), _textures["desk_n"].get(), pos * tmpM));
}

void WorldGenerator::buildrock(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["rock"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::buildUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::buildFloorUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["floor"].get(), _textures["floor_h"].get(), _textures["floor_n"].get(), pos));
}

void WorldGenerator::buildCailUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e)
{
	e.emplace_back(std::make_unique<Object>(_shaders["base"].get(), _shaders["shadow"].get(), _models["unit"].get(), _textures["wall"].get(), _textures["wall_h"].get(), _textures["wall_n"].get(), pos));
}

void WorldGenerator::loadShaders()
{
	_shaders.emplace("base", std::make_unique<ShaderProgram>("data/shaders/v_base_shader.glsl", "data/shaders/f_base_shader.glsl"));
	_shaders.emplace("camera", std::make_unique<ShaderProgram>("data/shaders/v_camera_shader.glsl", "data/shaders/f_camera_shader.glsl"));
	_shaders.emplace("light_src", std::make_unique<ShaderProgram>("data/shaders/v_light_src_shader.glsl", "data/shaders/f_light_src_shader.glsl"));
	_shaders.emplace("shadow", std::make_unique<ShaderProgram>("data/shaders/v_shadow_shader.glsl", "data/shaders/f_shadow_shader.glsl"));
	_shaders.emplace("particle", std::make_unique<ShaderProgram>("data/shaders/v_particle_shader.glsl", "data/shaders/f_particle_shader.glsl"));
}

void WorldGenerator::loadTextures()
{
	_textures.emplace("camera_ico", std::make_unique<Texture>("data/textures/c_ico.png",0, 0.f));
	_textures.emplace("skull", std::make_unique<Texture>("data/textures/skull.png", 8, 0.f));
	_textures.emplace("floor", std::make_unique<Texture>("data/textures/f.png", 256, 0.1f));
	_textures.emplace("floor_h", std::make_unique<Texture>("data/textures/f_h.png", 0, 0.f));
	_textures.emplace("floor_n", std::make_unique<Texture>("data/textures/f_n.png", 0, 0.f));
	_textures.emplace("wall", std::make_unique<Texture>("data/textures/wall.png", 128, 0.2f));
	_textures.emplace("wall_h", std::make_unique<Texture>("data/textures/wall_h.png", 0, 0.f));
	_textures.emplace("wall_n", std::make_unique<Texture>("data/textures/wall_n.png", 0, 0.f));

	_textures.emplace("t", std::make_unique<Texture>("data/textures/t.png", 128, 0.2f));
	_textures.emplace("t_h", std::make_unique<Texture>("data/textures/t_h.png", 0, 0.f));
	_textures.emplace("t_n", std::make_unique<Texture>("data/textures/t_n.png", 0, 0.f));

	_textures.emplace("particle", std::make_unique<Texture>("data/textures/part.png", 0, 0.f));
	_textures.emplace("desk", std::make_unique<Texture>("data/textures/desk.png", 8, 0.1f));
	_textures.emplace("desk_h", std::make_unique<Texture>("data/textures/desk_h.png",0, 0.f));
	_textures.emplace("desk_n", std::make_unique<Texture>("data/textures/desk_n.png", 0, 0.f));

}

void WorldGenerator::loadModels()
{
	_models.emplace("rock", std::make_unique<Model>("data/models/rock.obj"));
	_models.emplace("unit", std::make_unique<Model>("data/models/unit.obj"));
	_models.emplace("skull", std::make_unique <Model>("data/models/skull.obj"));
	_models.emplace("torch", std::make_unique <Model>("data/models/torch.obj"));
	_models.emplace("particle", std::make_unique <Model>("data/models/particle.obj"));
	_models.emplace("desk", std::make_unique <Model>("data/models/desk.obj"));
}
