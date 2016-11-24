#include "Human.h"
#include "Utilities.h"

#include <MexEngine/ResourceManager.h>

#include <SDL/SDL.h>

Human::Human(glm::vec4 posAndSize, float speed)
{
	_color.setColor(0, 0, getRandomNumb(100, 128));
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.z, posAndSize.w);
	_radius = _size.x / 2.0f;
	_speed = speed;
	_depth = 0.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;
	_direction = glm::vec2(getRandomNumb(-1.0f, 1.0f), getRandomNumb(-1.0f, 1.0f));

	_health = 200;
	_damage = 1;
}


Human::~Human()
{
}


void Human::move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies)
{
	glm::vec2 dest;


	Unit* closestEnemy = nullptr;
	float closestDist = (float)INT_MAX;

	for (size_t i = 0; i < enemies.size(); i++)
	{
		glm::vec2	distVec		= _getDistanceVec(enemies[i]);
		float		distance	= glm::length(distVec);

		if (distance < closestDist)
		{
			closestEnemy = enemies[i];
			closestDist = distance;
		}

	}

	if (closestDist < 700.0f && closestEnemy != nullptr)
	{
		dest = _getDistanceVec(closestEnemy);
		_direction = glm::normalize(dest);

		if (closestDist < 100.0f)
		{
			_direction *= -1.0f;
		}
		_position = _position + (_direction * (_speed * 2.0f));
	}
	else
	{
		float currTime = (float)SDL_GetTicks() / 1000;

		if (currTime - _dirChangingTime > getRandomNumb(0.5f, 6.5f))
		{
			dest = glm::vec2(getRandomNumb(-200.0f, 200.f), getRandomNumb(-200.0f, 200.f));
			
			_dirChangingTime = currTime;
			_direction = glm::normalize(dest);
			
		}
		_position = _position + (_direction * _speed);
	}
	

}