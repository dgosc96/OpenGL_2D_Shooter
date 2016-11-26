#include "Bullet.h"
#include <SDL/SDL.h>



#include "Utilities.h"

#include <MexEngine\TimeStep.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, float lifeTime, glm::vec2	size) :
	_direction	(dir),
	_lifeTime	(lifeTime)
{
	_position = pos;
	_speed = speed;
	_size = size;
	_radius = _size.x / 2.0f;
	_depth = 1.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/Bullet.png").id;

	_birthTime = SDL_GetTicks() / 1000.0f;

	_damage = 70;
	_attackSpeed = 0.0f;
	_lastAttackTime = 0.0f;

	_color.r = getRandomNumb(60, 255);
	_color.g = getRandomNumb(60, 255);
	_color.b = getRandomNumb(60, 255);
}


Bullet::~Bullet()
{
}




bool Bullet::update(const std::vector<std::string> &leveldata, std::vector<Unit*>& enemies, std::vector<Unit*>& humans)
{

	glm::vec2 newPos = _position + (_direction * _speed) * MexEngine::TimeStep::SM_Delta.getDeltaTime();

	float currTime = SDL_GetTicks() / 1000.0f;

	if (currTime - _birthTime > _lifeTime || collideWithUnits(enemies, humans, leveldata) || _canIMove(newPos, leveldata) == false)
	{
		return true;
	}

	_position = newPos;
	return false;


}


bool Bullet::_canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata)
{
	int xTileNumb = (int)(newPosition.x / TILE_WIDTH);

	int yTileNumb = (int)(newPosition.y / TILE_WIDTH);

	if (leveldata[yTileNumb][xTileNumb] == '#')
	{
		return false;
	}
	return true;

}

bool Bullet::collideWithUnits(std::vector<Unit*>& enemies,
	std::vector<Unit*>& allies, const std::vector<std::string> &levelData)
{

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (this != enemies[i] && enemies[i] != nullptr)
		{
			if (CollideWithUnit(enemies[i], levelData)) {
				
				if (attack(enemies[i]))
				{
					
					delete enemies[i];
					enemies[i] = enemies.back();
					enemies.pop_back();
				}
				
				_direction *= -1;

				return true;
			}

		}
	}

	for (size_t j = 1; j < allies.size(); j++)
	{
		if (this != allies[j])
		{
			if (CollideWithUnit(allies[j], levelData)) {
				
				_direction *= -1;



				return true;
			}

		}
	}
	return false;
}

bool Bullet::attack(Unit* target)
{

	bool isTargetDead = false;

		target->takeDMG(_damage);


		if (target->getHealth() <= 0)
		{

			isTargetDead = true;
		}

	return isTargetDead;

}