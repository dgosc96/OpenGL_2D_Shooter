#pragma once
#include "Unit.h"
class Human : public Unit
{
public:
	Human(){}
	Human(glm::vec4 posAndSize, float speed = 1.0f);

	virtual ~Human();
	

	virtual void move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies);


};

