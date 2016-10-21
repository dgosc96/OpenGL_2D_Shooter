#include "Bullet.h"
#include <iostream>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime, glm::vec2	size) :
	_direction	(dir),
	_lifeTime	(lifeTime)
{
	_position = pos;
	_speed = speed;
	_size = size;
	_depth = 1.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/Bullet.png").id;

}


Bullet::~Bullet()
{
}




bool Bullet::update(const std::vector<std::string> &leveldata)
{
	glm::vec2 newPos = _position + (_direction * _speed);
	_lifeTime--;

	if (_lifeTime == 0 || _canIMove(newPos, leveldata) == false)
	{
		return true;
	}

	_position = newPos;
	return false;


}


bool Bullet::_canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata)
{
	int xTileNumb = (int)newPosition.x / TILE_WIDTH;

	int yTileNumb = (int)newPosition.y / TILE_WIDTH;

	if (leveldata[yTileNumb][xTileNumb] == '#')
	{
		return false;
	}
	return true;

}