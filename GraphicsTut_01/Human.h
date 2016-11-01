#pragma once
#include "Unit.h"
class Human : public Unit
{
public:
	Human(){}
	Human(glm::vec4 posAndSize, float speed = 8.0f);
	~Human();
};

