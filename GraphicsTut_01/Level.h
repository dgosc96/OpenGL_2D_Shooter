#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>


#include "CONSTANTS.h"

#include "Enemy.h"
#include "Zombie.h"


class Level
{
public:
	Level(const std::string &filePath, std::vector<Unit*>& enemies);
	~Level();

	void loadFile(const std::string &filePath, std::vector<Unit*>& enemies);

	void draw();

	glm::vec2 getPlayerPos() { return _playerPos; }


	const std::vector<std::string>& getLevelData() const { return _levelData; }


private:
	std::vector<std::string>	_levelData;

	MexEngine::SpriteBatch		_spriteBatch;

	glm::vec2					_playerPos;


	void _setPlayerPos(glm::vec2 position) { _playerPos = position; }
};

