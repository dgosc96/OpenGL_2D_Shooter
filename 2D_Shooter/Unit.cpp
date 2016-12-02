#include "Unit.h"


#include "CONSTANTS.h"

#include <MexEngine/ResourceManager.h>

#include <algorithm>
#include <math.h>
#include <SDL\SDL.h>


#include <MexEngine\DEBUG.h>

#if DEBUG

#include <iostream>

#endif

#include "Utilities.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}


void Unit::draw(MexEngine::SpriteBatch& spriteBatch)
{

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(posAndSize, uv, m_textureID, m_depth, m_color);



}


bool Unit::CollideWithUnit(Unit* target, const std::vector<std::string> &levelData)
{
	bool didColide = false;

	float TARGET_UNIT_RADIUS = target->getSize().x / 2.0f;
	float MIN_DISTANCE = m_radius + TARGET_UNIT_RADIUS;

	glm::vec2 distVec = getDistanceVec(target);
	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth >= 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		glm::vec2 this_newPos = this->m_position + collisionDepthVec / 2.0f;
		glm::vec2 target_newPos = target->m_position - collisionDepthVec / 2.0f;


		if (canIMove(target_newPos, levelData))
		{
			this->m_position = this_newPos;
			target->m_position = target_newPos;
		}
		else
		{
			this->m_position += collisionDepthVec;
		}

		didColide = true;
	}

	return didColide;
}


bool Unit::collideWithUnits(std::vector<Unit*>& enemies,
	std::vector<Unit*>& allies, const std::vector<std::string> &levelData)
{
	bool didCollide = false;

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (this != enemies[i] && enemies[i] != nullptr)
		{
			if (CollideWithUnit(enemies[i], levelData)) {
				didCollide = true;
				m_direction *= -1;
			}

		}
	}

	for (size_t j = 0; j < allies.size(); j++)
	{
		if (this != allies[j])
		{
			if (CollideWithUnit(allies[j], levelData)) {
				didCollide = true;
				m_direction *= -1;
			}

		}
	}
	return didCollide;
}


bool Unit::collideWithLevel(const std::vector<std::string> &levelData)
{
	std::vector<CollidingTile> collidingTiles;
	bool didColide = false;

	checkTilePos(levelData,
		collidingTiles,
		m_position.x,
		m_position.y);

	checkTilePos(levelData,
		collidingTiles,
		m_position.x + m_size.x,
		m_position.y);

	checkTilePos(levelData,
		collidingTiles,
		m_position.x,
		m_position.y + m_size.y);

	checkTilePos(levelData,
		collidingTiles,
		m_position.x + m_size.x,
		m_position.y + m_size.y);


	if (collidingTiles.size() > 0)
	{
		sortCollidingTiles(collidingTiles, 0, collidingTiles.size() - 1);

		for (size_t i = 0; i < collidingTiles.size(); i++)
		{
			collideWithTile(collidingTiles[i].pos);
		}

		m_direction *= -1;
		didColide = true;
	}
	return didColide;

}


bool Unit::attack(Unit* target)
{
	float currTime = (float)SDL_GetTicks() / 1000;

	bool isTargetDead = false;

	if (currTime - m_lastAttackTime >= m_attackSpeed)
	{
		target->takeDMG(m_damage);


		if (target->getHealth() <= 0)
		{

			isTargetDead = true;
		}

		m_lastAttackTime = currTime;
	}

	return isTargetDead;

}


void Unit::takeDMG(int amount)
{
	float damageRatio = m_health / amount;

	m_health = m_health - amount;


	m_color.r -= m_color.r / damageRatio / 2;
	m_color.g -= m_color.g / damageRatio / 2;
	m_color.b -= m_color.b / damageRatio / 2;
}


glm::vec2 Unit::getDistanceVec(Unit* target)
{
	float TARGET_UNIT_RADIUS = target->getSize().x / 2.0f;

	glm::vec2 centerPosA = m_position + m_radius;
	glm::vec2 centerPosB = target->m_position + TARGET_UNIT_RADIUS;

	glm::vec2 distVec = centerPosA - centerPosB;

	return distVec;


}


void Unit::checkTilePos(const std::vector<std::string> &levelData,
	std::vector<CollidingTile> &collidingTiles,
	float x, float y)
{

	glm::vec2 cornerPos = glm::vec2(floor(x / TILE_WIDTH),
		floor(y / TILE_WIDTH));


	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{

		glm::vec2 collidingTilePos = (cornerPos * TILE_WIDTH) + (TILE_WIDTH / 2.0f);

		glm::vec2 centerPlayerPos = m_position + glm::vec2(m_radius);

		glm::vec2 distVec = centerPlayerPos - collidingTilePos;
		float distToPlayer = glm::length(distVec);


		collidingTiles.emplace_back(collidingTilePos, distToPlayer);
	}



}



void Unit::collideWithTile(glm::vec2 tilePos)
{
	float	MIN_DISTANCE = m_radius + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(m_radius);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);



	if (xDepth > 0 || yDepth > 0)
	{

		if (abs(xDepth) < abs(yDepth))
		{
			if (distVec.x < 0)
			{
				m_position.x -= xDepth;
			}
			else
			{
				m_position.x += xDepth;
			}

		}
		else
		{
			if (distVec.y < 0)
			{
				m_position.y -= yDepth;
			}
			else
			{
				m_position.y += yDepth;
			}

		}
	}


}

void Unit::sortCollidingTiles(std::vector<CollidingTile> &collidingTiles, int Left, int Right)
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
			swapCollidingTiles(collidingTiles, left, right);

			left++;
			right--;
		}

	} while (left <= right);

	if (Left < right)
	{
		sortCollidingTiles(collidingTiles, Left, right);
	}

	if (Right > left)
	{
		sortCollidingTiles(collidingTiles, left, Right);
	}

}


void Unit::swapCollidingTiles(std::vector<CollidingTile> &collidingTiles, int a, int b)
{
	CollidingTile buffer = collidingTiles[a];

	collidingTiles[a] = collidingTiles[b];

	collidingTiles[b] = buffer;

}

bool Unit::canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata)
{
	int xTileNumb = (int)(newPosition.x / TILE_WIDTH);

	int yTileNumb = (int)(newPosition.y / TILE_WIDTH);

	try
	{
		if (leveldata[yTileNumb][xTileNumb] == '#')
		{
			return false;
		}
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}



}

