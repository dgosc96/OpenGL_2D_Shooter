#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void draw(MexEngine::SpriteBatch& spriteBatch);

	//Returns true when bullet is out of life
	bool update();

private:
	int			_lifeTime;
	float		_speed;
	glm::vec2	_direction;
	glm::vec2	_position;
};

