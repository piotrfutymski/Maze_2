#pragma once

#include "entity.h"
#include "object.h"
#include "map"
#include "camera.h"
#include "Skull.h"
#include "lightSrc.h"


class WorldGenerator
{
public:

	void init();

	void load(const std::string & filename, std::vector<std::unique_ptr<Entity>>& e);


private:

	void buildRoofFloor(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int h);
	void buildWalls(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e, int h);
	void buildStairs(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);

	void buildLightSource(const glm::mat4& M, glm::vec3& pos, int c, std::vector<std::unique_ptr<Entity>>& e);
	void buildUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);
	void buildFloorUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);
	void buildCailUnit(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);
	void buildSkull(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);

	std::map<std::string, std::unique_ptr<Model>> _models;
	std::map<std::string, std::unique_ptr<Texture>> _textures;
	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaders;


private:

	void loadShaders();
	void loadTextures();
	void loadModels();


};