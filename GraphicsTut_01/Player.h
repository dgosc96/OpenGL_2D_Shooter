#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 


class Player
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, float speed);

	void draw(MexEngine::SpriteBatch& spriteBatch);
	void move(glm::vec2 direction);

	glm::vec2 getPosition() { return glm::vec2(_posAndSize.x, _posAndSize.y); }

private:
	float		_speed;
	glm::vec4	_posAndSize;


};

