#pragma once
#include "Enemy.h"
class Zombie : public Enemy
{
public:
	Zombie(glm::vec4 posAndSize, float speed = 14.0f);
	~Zombie();
};

