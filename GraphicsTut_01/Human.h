#pragma once
#include "Unit.h"
class Human : public Unit
{
public:
	Human(){}
	Human(glm::vec4 posAndSize, float speed = 2.0f);

	~Human();
	

	virtual void move();

private:
	glm::vec2 _direction;
	float	  _dirChangingTime;
};

