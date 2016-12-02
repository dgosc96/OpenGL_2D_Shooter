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

	glm::vec2 getPlayerPos() { return m_playerPos; }


	const std::vector<std::string>& getLevelData() const { return m_levelData; }


private:
	std::vector<std::string>	m_levelData;

	MexEngine::SpriteBatch		m_spriteBatch;

	glm::vec2					m_playerPos;


	void setPlayerPos(glm::vec2 position) { m_playerPos = position; }
};

