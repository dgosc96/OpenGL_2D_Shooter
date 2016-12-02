#pragma once
#include "Enemy.h"
#include "CONSTANTS.h"
class Zombie : public Enemy
{
public:
	Zombie(glm::vec2 pos, glm::vec2 size = glm::vec2(UNIT_WIDTH), float speed = 1.4f);
	~Zombie();


	void move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies);

private:
	void infect(std::vector<Unit*>& enemies, std::vector<Unit*>& allies, size_t killedEnemyINDX);
	


};

