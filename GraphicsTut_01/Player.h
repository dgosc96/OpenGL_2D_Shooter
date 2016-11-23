#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 
#include <MexEngine/InputManager.h>

#include "Bullet.h"
#include "CONSTANTS.h"
#include "Human.h"

class Player : public Human
{
public:
	Player(glm::vec4 posAndSize, float speed = 10.0f);
	~Player();

	void init(glm::vec4 posAndSize, float speed);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	bool processInput(	MexEngine::InputManager&		inputManager, 
						const std::vector<std::string>&	levelData,
						glm::vec2&						mouseCoords);
	void move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies){}
	void move(glm::vec2 direction);

	void shoot(	glm::vec2&	mouseCoords,
				float		spreadRange	= 8.0f,
				float		speed		= 55.0f,
				float		bulletSize	= 22.0f);

	void updateBullets(const  std::vector<std::string> &leveldata,									std::vector<Unit*>& enemies,
							  std::vector<Unit*>& humans);

	



protected:	



	std::vector<Bullet>		_bullets;



	 
};

