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

	bool update(const std::vector<std::string> &leveldata, 
					  std::vector<Unit*>& enemies,
					  std::vector<Unit*>& humans);

	bool attack(Unit* target);

	bool collideWithUnits(std::vector<Unit*>& enemies,
		std::vector<Unit*>& allies, const std::vector<std::string> &levelData);


protected:
	bool _canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata);


	int			_lifeTime;
	glm::vec2	_direction;


};

