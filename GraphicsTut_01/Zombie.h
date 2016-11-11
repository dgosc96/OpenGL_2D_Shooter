#pragma once
#include "Enemy.h"
class Zombie : public Enemy
{
public:
	Zombie(glm::vec4 posAndSize, float speed = 1.5f);
	~Zombie();


	void move(std::vector<Unit*>& enemies);

	
};

