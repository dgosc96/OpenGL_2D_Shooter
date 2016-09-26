#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>

#include "Wall.h"


class Level
{
public:
	Level();
	~Level();

	void loadFile(std::string filePath);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	glm::vec2 getPlayerPos() { return _playerPos; }

	std::vector<std::string> getLvlData() { return _levelData; }

private:
	std::vector<std::string>	_levelData;
	std::vector<Wall>			_walls;
	std::vector<Floor>			_floors;

	glm::vec2					_playerPos;


	void _setPlayerPos(glm::vec2 position) { _playerPos = position; }
};

