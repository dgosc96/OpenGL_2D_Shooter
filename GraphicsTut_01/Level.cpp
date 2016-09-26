#include "Level.h"

#include <fstream>

#include <MexEngine/Errors.h>
#include <iostream>

Level::Level()
{
}


Level::~Level()
{
}


void Level::loadFile(std::string filePath)
{
	std::ifstream LevelFile;
	LevelFile.open(filePath);

	if (LevelFile.fail())
	{
		MexEngine::fatalError("Failed to open level file. ");
	}


	std::string line;
	while (std::getline(LevelFile, line))
	{
		_levelData.push_back(line);


		static size_t y = 0;

		for (size_t x = 0; x < line.size(); x++)
		{
			switch (line[x])
			{
			case '#':
				_walls.emplace_back(glm::vec2(x * 50.0f, y * 50.0f), glm::vec2(50.0f, 50.0f), "Textures/other/PNG/wall.png");
				break;
			case ' ':
				_floors.emplace_back(glm::vec2(x * 50.0f, y * 50.0f), glm::vec2(50.0f, 50.0f), "Textures/other/PNG/floor.png");
				break;
			case '@':
				_setPlayerPos(glm::vec2(x * 50.0f, y * 50.0f));
				_floors.emplace_back(glm::vec2(x * 50.0f, y * 50.0f), glm::vec2(50.0f, 50.0f), "Textures/other/PNG/floor.png");
				break;
			default:
				break;
			}

		}
		y++;
	}

}

void Level::draw(MexEngine::SpriteBatch& spriteBatch)
{
	for (size_t i = 0; i < _floors.size(); i++)
	{
		_floors[i].draw(spriteBatch);
	}
	for (size_t i = 0; i < _walls.size(); i++)
	{
		_walls[i].draw(spriteBatch);
	}
}