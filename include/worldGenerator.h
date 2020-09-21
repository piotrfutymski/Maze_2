#pragma once

#include "entity.h"
#include "object.h"
#include "map"
#include "camera.h"
#include "Skull.h"


class WorldGenerator
{
public:

	void init();

	void load(const std::string & filename, std::vector<std::unique_ptr<Entity>>& e);


private:

	void buildBaseMazeElement(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);
	void buildWallElement(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);

	void buildWall(const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);
	void buildSkull(const glm::vec3& p, const glm::mat4& pos, std::vector<std::unique_ptr<Entity>>& e);

	std::map<std::string, std::unique_ptr<Model>> _models;
	std::map<std::string, std::unique_ptr<Texture>> _textures;
	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaders;


private:

	void loadShaders();
	void loadTextures();
	void loadModels();


};