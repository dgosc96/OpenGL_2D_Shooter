#include "Unit.h"
#include "CONSTANTS.h"

#include <MexEngine/ResourceManager.h>
#include <algorithm>
#include <math.h>



Unit::Unit()
{
}


Unit::~Unit()
{
}



void Unit::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);

	spriteBatch.draw(posAndSize, uv, _textureID, _depth, _color);



}

void Unit::_collideWithLevel(const std::vector<std::string> &leveldata)
{
	std::vector<CollidingTile> collidingTiles;

	_checkTilePos(leveldata,
		collidingTiles,
		_position.x,
		_position.y);

	_checkTilePos(leveldata,
		collidingTiles,
		_position.x + UNIT_WIDTH,
		_position.y);

	_checkTilePos(leveldata,
		collidingTiles,
		_position.x,
		_position.y + UNIT_WIDTH);

	_checkTilePos(leveldata,
		collidingTiles,
		_position.x + UNIT_WIDTH,
		_position.y + UNIT_WIDTH);


	if (collidingTiles.size() > 0)
	{
		_sortCollidingTiles(collidingTiles, 0, collidingTiles.size() - 1);

		for (size_t i = 0; i < collidingTiles.size(); i++)
		{
			_collideWithTile(collidingTiles[i].pos);
		}
	}


}


void Unit::_checkTilePos(const std::vector<std::string> &levelData,
	std::vector<CollidingTile> &collidingTiles,
	float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / TILE_WIDTH),
									floor(y / TILE_WIDTH));

	if (levelData[cornerPos.y][cornerPos.x] != ' ')
	{

		glm::vec2 collidingTilePos = (cornerPos * TILE_WIDTH) + (TILE_WIDTH / 2.0f);

		glm::vec2 centerPlayerPos = _position + glm::vec2(UNIT_RADIUS);

		glm::vec2 distVec = centerPlayerPos - collidingTilePos;
		float distToPlayer = sqrt((distVec.x * distVec.x) + (distVec.y * distVec.y));


		collidingTiles.emplace_back(collidingTilePos, distToPlayer);
	}
}



void Unit::_collideWithTile(glm::vec2 tilePos)
{
	const float	MIN_DISTANCE = UNIT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(UNIT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);



	if (xDepth > 0 || yDepth > 0)
	{

		if (abs(xDepth) < abs(yDepth))
		{
			if (distVec.x < 0)
			{
				_position.x -= xDepth;
			}
			else
			{
				_position.x += xDepth;
			}
			
		}
		else
		{
			if (distVec.y < 0)
			{
				_position.y -= yDepth;
			}
			else
			{
				_position.y += yDepth;
			}

		}
	}


}

void Unit::_sortCollidingTiles(std::vector<CollidingTile> &collidingTiles, int Left, int Right)
{
	

	int left = Left;
	int right = Right;

	CollidingTile middleOfArr = collidingTiles[left + right / 2];

	do
	{
		while (collidingTiles[left].distToPlayer < middleOfArr.distToPlayer)
		{
			left++;
		}

		while (collidingTiles[right].distToPlayer > middleOfArr.distToPlayer)
		{
			right--;
		}

		if (left <= right)
		{
			_swapCollidingTiles(collidingTiles, left, right);

			left++;
			right--;
		}

	} while (left <= right);

	if (Left < right)
	{
		_sortCollidingTiles(collidingTiles, Left, right);
	}

	if (Right > left)
	{
		_sortCollidingTiles(collidingTiles, left, Right);
	}

}


void Unit::_swapCollidingTiles(std::vector<CollidingTile> &collidingTiles, int a, int b)
{
	CollidingTile buffer = collidingTiles[a];

	collidingTiles[a] = collidingTiles[b];

	collidingTiles[b] = buffer;

}