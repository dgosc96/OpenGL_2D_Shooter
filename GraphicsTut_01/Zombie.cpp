#include "Zombie.h"
#include <MexEngine/ResourceManager.h> 
#include "Utilities.h"
#include <iostream>

#include <SDL/SDL.h>


Zombie::Zombie(glm::vec2 pos, glm::vec2 size, float speed)
{
	_color.setColor(0, getRandomNumb(100, 128), 0);
	_position = pos;
	_size = size;
	_radius = _size.x / 2.0f;
	_speed = speed;
	_depth = 0.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;

	_damage = 10;
	_health = 250;
	_attackSpeed = 0.25f;

	_lastAttackTime = 0.0f;

}


Zombie::~Zombie()
{
}



void Zombie::move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies)
{
	glm::vec2 dest;

	Unit* closestEnemy = nullptr;
	int	  closestEnemyIndex = NULL;
	float closestDist = (float)INT_MAX;

	for (size_t i = 0; i < enemies.size(); i++)
	{
		glm::vec2	distVec = _getDistanceVec(enemies[i]);
		float		distance = glm::length(distVec);

		if (distance < closestDist)
		{
			closestEnemy = enemies[i];
			closestEnemyIndex = i;
			closestDist = distance;

		}

	}


	if ((closestDist < 700.0f) && closestEnemy != nullptr)
	{
		dest = _getDistanceVec(closestEnemy) * -1.0f;
		_direction = glm::normalize(dest);
		_position = _position + (_direction * (_speed * 3.0f));

		closestDist = glm::length(_getDistanceVec(closestEnemy));

		if (closestDist <= UNIT_WIDTH)
		{
			if (attack(closestEnemy) == true)
			{
				_infect(enemies, allies, closestEnemyIndex);

			}
		}

	}
	else
	{
		float currTime = (float)SDL_GetTicks() / 1000.0f;

		if (currTime - _dirChangingTime > getRandomNumb(3.5f, 5.5f) || currTime < 10.0f)
		{
			dest = glm::vec2(getRandomNumb(-200.0f, 200.0f), getRandomNumb(-200.0f, 200.0f));

			_dirChangingTime = currTime;
			_direction = glm::normalize(dest);


		}
		_position = _position + (_direction * _speed);
	}


}


void Zombie::_infect(std::vector<Unit*>& enemies, std::vector<Unit*>& allies, size_t killedEnemyINDX)
{

	allies.push_back(new Zombie(enemies[killedEnemyINDX]->getPosition(), 
								enemies[killedEnemyINDX]->getSize()));

	delete enemies[killedEnemyINDX];
	enemies[killedEnemyINDX] = nullptr;

	enemies[killedEnemyINDX] = enemies.back();
	enemies.pop_back();

}