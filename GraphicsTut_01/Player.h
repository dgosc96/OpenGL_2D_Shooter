#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 
#include <MexEngine/InputManager.h>

#include "Bullet.h"
#include "CONSTANTS.h"
#include "Unit.h"

class Player : public Unit
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, float speed);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	bool processInput(	MexEngine::InputManager&		inputManager, 
						const std::vector<std::string>&	levelData,
						glm::vec2&						mouseCoords);


	void shoot(	glm::vec2&	mouseCoords,
				float		spreadRange	= 8.0f,
				float		speed		= 25.0f,
				float		bulletSize	= 12.0f);

	void updateBullets(const std::vector<std::string> &leveldata);

	glm::vec2 getPosition() { return _position; }



protected:	
	void _move(glm::vec2 direction, const std::vector<std::string>& levelData);


	std::vector<Bullet>		_bullets;



	 
};

