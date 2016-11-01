#include "Level.h"

#include <fstream>
#include <iostream>

#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>



Level::Level(const std::string &filePath, std::vector<Unit*>&  enemies)
{
	_spriteBatch.init();
	loadFile(filePath, enemies);
	

}


Level::~Level()
{
}


void Level::loadFile(const std::string &filePath, std::vector<Unit*>& enemies)
{
	GLint wallTexture = MexEngine::ResourceManager::getTexture("Textures/other/PNG/wall.png").id;
	GLint floorTexture = MexEngine::ResourceManager::getTexture("Textures/other/PNG/floor.png").id;


	std::ifstream LevelFile;
	LevelFile.open(filePath);

	if (LevelFile.fail())
	{
		MexEngine::fatalError("Failed to open level file. ");
	}

	_spriteBatch.begin();

	MexEngine::Color color;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	std::string line;

	size_t y = 0;

	while (std::getline(LevelFile, line))
	{

		for (size_t x = 0; x < line.size(); x++)
		{

			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);


			switch (line[x])
			{
			case '#':
				_spriteBatch.draw(destRect, uvRect, wallTexture, 0.0f, color);

				break;
			case '.':
				_spriteBatch.draw(destRect, uvRect, floorTexture, 0.0f, color);

				break;
			case '@':
				_setPlayerPos(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));

				line[x] = '.';
				_spriteBatch.draw(destRect, uvRect, floorTexture, 0.0f, color);
				break;
			case 'Z':
				enemies.push_back(new Zombie(glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, UNIT_WIDTH, UNIT_WIDTH)));

				line[x] = '.';
				_spriteBatch.draw(destRect, uvRect, floorTexture, 0.0f, color);
			default:
				break;
			}

		}
		_levelData.push_back(line);
		y++;
	}
	
	_spriteBatch.end();
}

void Level::draw()
{
	_spriteBatch.renderBatch();
}