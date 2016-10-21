#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 

#include "CONSTANTS.h"

#include "Unit.h"


class Bullet : public Unit
{
public:
	Bullet(	glm::vec2	pos, 
			glm::vec2	dir, 
			float		speed, 
			int			lifeTime, 
			glm::vec2	size);
	~Bullet();

	bool update(const std::vector<std::string> &leveldata);

protected:
	bool _canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata);


	int			_lifeTime;
	glm::vec2	_direction;


};

