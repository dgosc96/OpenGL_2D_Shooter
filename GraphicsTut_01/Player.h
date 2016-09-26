#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 

#include "Bullet.h"


class Player
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, float speed);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	void move(glm::vec2 direction);
	void shoot(glm::vec2& mouseCoords, float spreadRange = 15.0f, float speed = 25.0f);

	void updateBullets();

	glm::vec2 getPosition() { return glm::vec2(_posAndSize.x, _posAndSize.y); }

	void setLvlData(std::vector<std::string>& leveldata) { _leveldata = leveldata; }

private:
	bool					_canIMove (glm::vec2 newPosition);
	float					_speed;

	glm::vec4				_posAndSize;
	glm::vec2				_position;
	glm::vec2				_size;
	MexEngine::GLTexture	_texture;

	std::vector<Bullet>		_bullets;

	std::vector<std::string> _leveldata;


	 
};

